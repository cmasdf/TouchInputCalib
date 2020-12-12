/**
 * @file Mapping.cpp
 * @author Daniel Matthes
 * @date 08.12.2020
 */

#include <QDebug>
#include <QPointF>
#include <src/Mapping.h>

Mapping::Mapping(QVector<Monitor_t> monitorDevices, QVector<InputDevices_t> inputDevices,
                 MainAreaBackend *mainAreaBackend, QQmlApplicationEngine *qmlEngine)
                 {
    // register meta types to facilitate the connection of queue arguments
    qRegisterMetaType< QPointF >("QPointF");

    m_listOfMonitors = std::move(monitorDevices);
    m_listOfInputDevices = std::move(inputDevices);
    m_mainAreaBackend = mainAreaBackend;
    m_qmlEngine = qmlEngine;
    m_numberOfReceivedTouchInputs = 0;

    // incoming signals
    // connection between MainAreaBackend and Mapping
    connect(m_mainAreaBackend, &MainAreaBackend::touchAreaClicked, this, &Mapping::touchAreaClicked );

    m_numberOfScreens = m_listOfMonitors.size();

    for (int i = 0 ; i < m_numberOfScreens; i++) {
        Display *display = XOpenDisplay(nullptr);
        mapOutputXrandr(display, m_listOfInputDevices[i].id, m_listOfMonitors[i].nameString);
        qDebug() << "xinput map-to-output" << m_listOfInputDevices[i].id << m_listOfMonitors[i].nameString;
        XCloseDisplay(display);

        PhysicalDisplay_t phyDpy;

        auto wnd = m_qmlEngine->rootObjects()[0]->findChild<QQuickWindow *>("applicationWindow" + QString::number(i));
        if (wnd) {
            phyDpy.window = wnd;
        } else {
            phyDpy.window = nullptr;
        }
        phyDpy.port                 = m_listOfMonitors[i].nameString;
        phyDpy.inputDeviceID        = m_listOfInputDevices[i].id;
        phyDpy.targetTouchPoint     = {wnd->x() + wnd->width()/2, wnd->y() + wnd->height()/2};
        phyDpy.actualTouchPoint     = {0,0};
        phyDpy.mappingSuccessful    = false;

        m_listOfPhysicalDisplays.append(phyDpy);
    }
}

Mapping::~Mapping() = default;

void Mapping::mappingStart() {
    m_listOfPhysicalDisplays[0].window->setProperty("touchAreaVisible", true);
}

void Mapping::touchAreaClicked(QPointF point) {
    qDebug() << "Touch area clicked";

    int idx = m_numberOfReceivedTouchInputs;
    QQuickWindow * currentWindow = m_listOfPhysicalDisplays[idx].window;
    m_listOfPhysicalDisplays[idx].actualTouchPoint = point.toPoint();
    if (m_listOfPhysicalDisplays[idx].actualTouchPoint == m_listOfPhysicalDisplays[idx].targetTouchPoint) {
        m_listOfPhysicalDisplays[idx].mappingSuccessful = true;
    }

    qDebug() << "targetTouchPoint:" << m_listOfPhysicalDisplays[idx].targetTouchPoint
             << "actualTouchPoint:" << m_listOfPhysicalDisplays[idx].actualTouchPoint;

    currentWindow->setProperty("showResult", true);
    currentWindow->setProperty("touchAreaVisible", false);

    m_numberOfReceivedTouchInputs++;

    if (m_numberOfReceivedTouchInputs == m_numberOfScreens) {
        bool complete = true;

        for (const auto &phyDpy : m_listOfPhysicalDisplays) {
            complete &= phyDpy.mappingSuccessful;
        }

        if (complete) {
            for (const auto &phyDpy : m_listOfPhysicalDisplays) {
                phyDpy.window->setProperty("touchAreaActive", false);
            }
            m_listOfPhysicalDisplays[0].window->setProperty("userInfo", "Mapping successful!");
            m_listOfPhysicalDisplays[0].window->setProperty("showResult", false);
            m_listOfPhysicalDisplays[0].window->setProperty("touchAreaVisible", true);
            qDebug() << "Mapping successful!";
            return;
        } else {
            m_numberOfReceivedTouchInputs = 0;

            QVector<PhysicalDisplay_t> listOfPhysDpyCopy = m_listOfPhysicalDisplays;


            for (auto &phyDpy : m_listOfPhysicalDisplays) {
                if (!phyDpy.mappingSuccessful) {
                    for(auto const &element : listOfPhysDpyCopy) {
                        if (phyDpy.targetTouchPoint == element.actualTouchPoint) {
                            phyDpy.inputDeviceID = element.inputDeviceID;
                            break;
                        }
                    }
                    Display *display = XOpenDisplay(nullptr);
                    mapOutputXrandr(display, phyDpy.inputDeviceID, phyDpy.port);
                    qDebug() << "xinput map-to-output" << phyDpy.inputDeviceID << phyDpy.port;
                    XCloseDisplay(display);
                }
            }
        }
    }

    m_listOfPhysicalDisplays[m_numberOfReceivedTouchInputs].window->setProperty("showResult", false);
    m_listOfPhysicalDisplays[m_numberOfReceivedTouchInputs].window->setProperty("touchAreaVisible", true);
}

int Mapping::mapOutputXrandr(Display *dpy, int deviceId, const char *outputName) {
    int rc = EXIT_FAILURE;
    XRRScreenResources *res;
    XRROutputInfo *outputInfo;

    res = XRRGetScreenResources(dpy, DefaultRootWindow(dpy));
    outputInfo = findOutputXrandr(dpy, outputName);

    /* crtc holds our screen info, need to compare to actual screen size */
    if (outputInfo) {
        XRRCrtcInfo *crtcInfo;
        Matrix m;
        matrixSetUnity(&m);
        crtcInfo = XRRGetCrtcInfo(dpy, res, outputInfo->crtc);
        setTransformationMatrix(dpy, &m, crtcInfo->x, crtcInfo->y, crtcInfo->width, crtcInfo->height,
                                crtcInfo->rotation);
        rc = applyMatrix(dpy, deviceId, &m);
        XRRFreeCrtcInfo(crtcInfo);
        XRRFreeOutputInfo(outputInfo);
    } else {
        printf("Unable to find output '%s'. Output may not be connected.\n", outputName);
    }

    XRRFreeScreenResources(res);

    return rc;
}

/* Caller must free return value */
XRROutputInfo *Mapping::findOutputXrandr(Display *dpy, const char *outputName) {
    XRRScreenResources *res;
    XRROutputInfo *outputInfo = nullptr;
    int i;
    int found = 0;

    res = XRRGetScreenResources(dpy, DefaultRootWindow(dpy));

    for (i = 0; i < res->noutput; i++) {
        outputInfo = XRRGetOutputInfo(dpy, res, res->outputs[i]);

        if (outputInfo->crtc && outputInfo->connection == RR_Connected && strcmp(outputInfo->name, outputName) == 0) {
            found = 1;
            break;
        }

        XRRFreeOutputInfo(outputInfo);
    }

    XRRFreeScreenResources(res);

    if (!found) {
        outputInfo = nullptr;
    }

    return outputInfo;
}

void Mapping::matrixSet(Matrix *m, int row, int col, float val) {
    m->m[row * 3 + col] = val;
}

void Mapping::matrixSetUnity(Matrix *m) {
    memset(m, 0, sizeof(m->m));
    matrixSet(m, 0, 0, 1);
    matrixSet(m, 1, 1, 1);
    matrixSet(m, 2, 2, 1);
}

void Mapping::matrixPrint(const Matrix *m) {
    printf("[ %3.3f %3.3f %3.3f ]\n", m->m[0], m->m[1], m->m[2]);
    printf("[ %3.3f %3.3f %3.3f ]\n", m->m[3], m->m[4], m->m[5]);
    printf("[ %3.3f %3.3f %3.3f ]\n", m->m[6], m->m[7], m->m[8]);
}

int Mapping::applyMatrix(Display *dpy, int deviceId, Matrix *m) {
    Atom propFloat, propMatrix;

    union {
        unsigned char *c;
        float *f;
    } data = {};
    int formatReturn;
    Atom typeReturn;
    unsigned long nItems;
    unsigned long bytesAfter;

    int rc;

    propFloat = XInternAtom(dpy, "FLOAT", False);
    propMatrix = XInternAtom(dpy, "Coordinate Transformation Matrix", False);

    if (!propFloat) {
        fprintf(stderr, "Float atom not found. This server is too old.\n");
        return EXIT_FAILURE;
    }
    if (!propMatrix) {
        fprintf(stderr, "Coordinate transformation matrix not found. This "
                        "server is too old\n");
        return EXIT_FAILURE;
    }

    rc = XIGetProperty(dpy, deviceId, propMatrix, 0, 9, False, propFloat, &typeReturn, &formatReturn,
                       &nItems, &bytesAfter, &data.c);
    if (rc != Success || propFloat != typeReturn || formatReturn != 32 || nItems != 9 || bytesAfter != 0) {
        fprintf(stderr, "Failed to retrieve current property values\n");
        return EXIT_FAILURE;
    }

    memcpy(data.f, m->m, sizeof(m->m));

    XIChangeProperty(dpy, deviceId, propMatrix, propFloat, formatReturn, PropModeReplace, data.c, nItems);

    XFree(data.c);

    return EXIT_SUCCESS;
}

void Mapping::matrixS4(Matrix *m, float x02, float x12, float d1, float d2, int mainDiag) {
    matrixSet(m, 0, 2, x02);
    matrixSet(m, 1, 2, x12);

    if (mainDiag) {
        matrixSet(m, 0, 0, d1);
        matrixSet(m, 1, 1, d2);
    } else {
        matrixSet(m, 0, 0, 0);
        matrixSet(m, 1, 1, 0);
        matrixSet(m, 0, 1, d1);
        matrixSet(m, 1, 0, d2);
    }
}

void Mapping::setTransformationMatrix(Display *dpy, Matrix *m, int offset_x, int offset_y, int screen_width,
                                      int screen_height, int rotation) {
    /* total display size */
    int width = DisplayWidth(dpy, DefaultScreen(dpy));
    int height = DisplayHeight(dpy, DefaultScreen(dpy));

    /* offset */
    float x = 1.0 * offset_x / width;
    float y = 1.0 * offset_y / height;

    /* mapping */
    float w = 1.0 * screen_width / width;
    float h = 1.0 * screen_height / height;

    matrixSetUnity(m);

    /*
     * There are 16 cases:
     * Rotation X Reflection
     * Rotation: 0 | 90 | 180 | 270
     * Reflection: None | X | Y | XY
     *
     * They are spelled out instead of doing matrix multiplication to avoid
     * any floating point errors.
     */
    switch (rotation) {
        case RR_Rotate_0:
        case RR_Rotate_180 | RR_Reflect_All:
            matrixS4(m, x, y, w, h, 1);
            break;
        case RR_Reflect_X | RR_Rotate_0:
        case RR_Reflect_Y | RR_Rotate_180:
            matrixS4(m, x + w, y, -w, h, 1);
            break;
        case RR_Reflect_Y | RR_Rotate_0:
        case RR_Reflect_X | RR_Rotate_180:
            matrixS4(m, x, y + h, w, -h, 1);
            break;
        case RR_Rotate_90:
        case RR_Rotate_270 | RR_Reflect_All: /* left limited - correct in working zone. */
            matrixS4(m, x + w, y, -w, h, 0);
            break;
        case RR_Rotate_270:
        case RR_Rotate_90 | RR_Reflect_All: /* left limited - correct in working zone. */
            matrixS4(m, x, y + h, w, -h, 0);
            break;
        case RR_Rotate_90 | RR_Reflect_X: /* left limited - correct in working zone. */
        case RR_Rotate_270 | RR_Reflect_Y: /* left limited - correct in working zone. */
            matrixS4(m, x, y, w, h, 0);
            break;
        case RR_Rotate_90 | RR_Reflect_Y: /* right limited - correct in working zone. */
        case RR_Rotate_270 | RR_Reflect_X: /* right limited - correct in working zone. */
            matrixS4(m, x + w, y + h, -w, -h, 0);
            break;
        case RR_Rotate_180:
        case RR_Reflect_All | RR_Rotate_0:
            matrixS4(m, x + w, y + h, -w, -h, 1);
            break;
        default:
            break;
    }

#ifdef DEBUG
    matrixPrint(m);
#endif
}
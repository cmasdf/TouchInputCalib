/**
 * @file Mapping.h
 * @author Daniel Matthes
 * @date 08.12.2020
 * @brief mapping of active monitors and touch input devices
 */
#ifndef MAPPING_H
#define MAPPING_H

#include <QObject>
#include <QVector>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <X11/Xlib.h>
#include <X11/extensions/XInput2.h>
#include <src/Monitor.h>
#include <src/InputDevice.h>
#include <src/MainAreaBackend.h>

typedef struct {
    float m[9];
} Matrix;

typedef struct {
    QQuickWindow* window;
    char* port;
    int inputDeviceID;
    QPoint targetTouchPoint;
    QPoint actualTouchPoint;
    bool mappingSuccessful;
} PhysicalDisplay_t;

#define RR_Reflect_All	(RR_Reflect_X|RR_Reflect_Y)

class Mapping : public QObject {
Q_OBJECT
public:
    Mapping(QVector<Monitor_t> monitorDevices, QVector<InputDevices_t> inputDevices, MainAreaBackend *mainAreaBackend,
            QQmlApplicationEngine *qmlEngine);
    ~Mapping() override;

    void mappingStart();

public slots:
    void touchAreaClicked(QPointF point);

private:
    static int mapOutputXrandr(Display *dpy, int deviceId, const char *outputName);
    static XRROutputInfo* findOutputXrandr(Display *dpy, const char *outputName);
    static void matrixSet(Matrix *m, int row, int col, float val);
    static void matrixSetUnity(Matrix *m);
    static void matrixPrint(const Matrix *m);
    static int applyMatrix(Display *dpy, int deviceId, Matrix *m);
    static void matrixS4(Matrix *m, float x02, float x12, float d1, float d2, int main_diag);
    static void setTransformationMatrix(Display *dpy, Matrix *m, int offset_x, int offset_y, int screen_width,
                                        int screen_height, int rotation);

    QVector<Monitor_t> m_listOfMonitors = {};
    QVector<InputDevices_t> m_listOfInputDevices = {};
    QVector<PhysicalDisplay_t> m_listOfPhysicalDisplays;
    MainAreaBackend *m_mainAreaBackend;                     ///< instance of MainAreaBackend module
    QQmlApplicationEngine *m_qmlEngine;                     ///< instance of QML engine
    int m_numberOfScreens;                                  ///< number of detected screens
    int m_numberOfReceivedTouchInputs;                      ///< number of received touch input events
};

#endif //MAPPING_H

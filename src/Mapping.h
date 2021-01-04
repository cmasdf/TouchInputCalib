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

/**
 * @brief calibration matrix structure
 */
typedef struct {
    float m[9];
} Matrix;

/**
 * @brief physical display data structure
 */
typedef struct {
    /**
     * @name physical display keys
     */
    ///@{
    QQuickWindow* window;               ///< pointer to quick item
    char* port;                         ///< monitor port
    int inputDeviceID;                  ///< input device id
    QPoint targetTouchPoint;            ///< coordinate which has to be touched
    QPoint actualTouchPoint;            ///< coordinate which was actually touched
    bool mappingSuccessful;             ///< mapping successful flag
    ///@}
} PhysicalDisplay_t;

#define RR_Reflect_All	(RR_Reflect_X|RR_Reflect_Y)

/**
 * @class Mapping class
 *
 * @brief Does mapping of monitors and touch input devices
 */
class Mapping : public QObject {
Q_OBJECT
public:
    /**
     * @brief Constructor
     * @param monitorDevices - list of active monitors
     * @param inputDevices - list of touch input devices
     * @param mainAreaBackend - instance of mainArea backend
     * @param qmlEngine - instance to qml engine
     */
    Mapping(QVector<Monitor_t> monitorDevices, QVector<InputDevices_t> inputDevices, MainAreaBackend *mainAreaBackend,
            QQmlApplicationEngine *qmlEngine);

    /**
     * @brief Destructor
     */
    ~Mapping() override;

    /**
     * @brief Start display 2 touch input device mapping procedure
     */
    void mappingStart();

public slots:
    /**
     * @brief Slot is called, if a certain touch area was clicked
     * @param point - touchPoint
     */
    void touchAreaClicked(QPointF point);

private:
    /**
     * @name functions for mapping touch input devices to monitors
     *
     * The first function 'mapOutputXrandr' does the mapping. All following functions
     * are called from this function. All functions are copied from the transform.c module
     * from https://github.com/freedesktop/xorg-xinput
     */
    ///@{
    static int mapOutputXrandr(Display *dpy, int deviceId, const char *outputName);
    static XRROutputInfo* findOutputXrandr(Display *dpy, const char *outputName);
    static void matrixSet(Matrix *m, int row, int col, float val);
    static void matrixSetUnity(Matrix *m);
    static void matrixPrint(const Matrix *m);
    static int applyMatrix(Display *dpy, int deviceId, Matrix *m);
    static void matrixS4(Matrix *m, float x02, float x12, float d1, float d2, int main_diag);
    static void setTransformationMatrix(Display *dpy, Matrix *m, int offset_x, int offset_y, int screen_width,
                                        int screen_height, int rotation);
    ///@}

    QVector<Monitor_t> m_listOfMonitors = {};               ///< list containing specification of all active monitors
    QVector<InputDevices_t> m_listOfInputDevices = {};      ///< list containing specification of all touch screens
    QVector<PhysicalDisplay_t> m_listOfPhysicalDisplays;    ///< list of all physical displays (combinations of touch inputs and monitors)
    MainAreaBackend *m_mainAreaBackend;                     ///< instance of MainAreaBackend module
    QQmlApplicationEngine *m_qmlEngine;                     ///< instance of QML engine
    int m_numberOfScreens;                                  ///< number of detected screens
    int m_numberOfReceivedTouchInputs;                      ///< number of received touch input events
};

#endif //MAPPING_H

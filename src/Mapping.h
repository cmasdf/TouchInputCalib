/**
 * @file Mapping.h
 * @author Daniel Matthes
 * @date 08.12.2020
 * @brief mapping of active monitors and touch input devices
 */
#ifndef MAPPING_H
#define MAPPING_H

#include <QVector>
#include <X11/Xlib.h>
#include <X11/extensions/XInput2.h>
#include <src/Monitor.h>
#include <src/InputDevice.h>

typedef struct {
    float m[9];
} Matrix;

#define RR_Reflect_All	(RR_Reflect_X|RR_Reflect_Y)

class Mapping {
public:
    Mapping(QVector<Monitor_t> monitorDevices, QVector<InputDevices_t> inputDevices);
    ~Mapping();

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
};


#endif //MAPPING_H

#pragma once
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <qopenglbuffer.h>
class Canvas : public QOpenGLWidget, protected QOpenGLExtraFunctions
{

public:
    Canvas(QWidget *parent = nullptr);
    ~Canvas();

    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void createBuffers();

    QVector3D pointFromScreen(QVector3D point);

    std::vector<QVector3D> updateBezierCurve( std::vector< QVector3D > controlPoints);
    void updateVertexBuffer();
    void createVAO();
private:
    std::vector< QVector3D > _points; //vetor de pontos que são clicados
    QOpenGLShaderProgram* _program;
    unsigned int _pointsBuffer = static_cast<unsigned int>(-1); //Buffer para os pontos, as retas e a Bezier

    QMatrix4x4 _view;
    QMatrix4x4 _proj;
    QOpenGLVertexArrayObject _vao;

};

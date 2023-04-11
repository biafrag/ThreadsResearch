#include "include/canvas.h"
#include <QMouseEvent>
#include <QApplication>
const char* vertexShaderSource = R"(
    #version 330 core
    layout( location = 0 ) in vec3 vertexPos;
    uniform mat4 transformMatrix;
    void main()
    {
        gl_Position = transformMatrix * vec4( vertexPos, 1 );
    }
)";


const char* fragmentShaderSource = R"(
    #version 330 core
    uniform vec3 color;
    out vec3 finalColor;
    void main()
    {
        finalColor = color;
    }
)";

Canvas::Canvas(QWidget *parent)
    : QOpenGLWidget(parent)

{
}



Canvas::~Canvas()
{
}



void Canvas::initializeGL()
{
    initializeOpenGLFunctions();

    makeCurrent();

    glViewport(0, 0, width(), height());

    _program = new QOpenGLShaderProgram();
    _program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    _program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    _program->link();

    if (!_program->isLinked())
    {
        printf("Nao foi possivel linkar programa\n");
    }

    _program->bind();

    createBuffers();
    createVAO();


}



void Canvas::paintGL()
{
    _program->bind();
    _vao.bind();

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_POINT_SMOOTH);
    glPointSize(8.0f);
    _program->setUniformValue("color", QVector3D(1, 0, 0));

    _program->setUniformValue("transformMatrix", _proj * _view);

    //Desenha os pontos
    glDrawArrays(GL_POINTS, 0, (int)_points.size());
    _vao.release();

}



void Canvas::resizeGL(int width, int height)
{
    //_proj.ortho(-width/2.0, width/2.0, -height/2.0, height/2.0, -1.f, 1.0f);
    //_proj.ortho(-1, 1, -1, 1, -1.f, 1.0f);

    glViewport(0, 0, width, height);
}



void Canvas::mousePressEvent(QMouseEvent *event)
{
}



void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    update();
}



void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    QVector3D point = pointFromScreen(QVector3D(event->x(), height() - event->y(), 0));

    if(event->button() == Qt::LeftButton)
    {
        _points.push_back(point);
        updateVertexBuffer();
    }
     update();
}



void Canvas::createBuffers()
{
    _program->bind();
    glGenBuffers(1, &_pointsBuffer);
    updateVertexBuffer();

}



QVector3D Canvas::pointFromScreen(QVector3D point)
{
    point = point.unproject( _view, _proj, QRect(0, 0, width(),height()));
    point.setZ(0.f);
    return point;
}



std::vector<QVector3D> Canvas::updateBezierCurve(std::vector<QVector3D> controlPoints)
{
    std::vector< QVector3D > aux;
    float x, y;
    if(controlPoints.size() == 2)
    {
        for (float t = 0;t < 1;t = t + 0.01)
        {
            x =(1-t) * controlPoints[0].x() + t * controlPoints[1].x();
            y = (1-t) * controlPoints[0].y() + t * controlPoints[1].y();
            aux.push_back(QVector3D(x, y, 0));
        }
    }
    else if(controlPoints.size()==3)
    {
        for (float t = 0;t < 1;t = t + 0.01)
        {
            x = (1 - t)*(1 - t)*controlPoints[0].x() + 2 * t*(1 - t)*controlPoints[1].x() + t*t*controlPoints[2].x();
            y = (1 - t)*(1 - t)*controlPoints[0].y() + 2 * t*(1 - t)*controlPoints[1].y() + t*t*controlPoints[2].y();
            aux.push_back(QVector3D(x, y, 0));
        }
    }
    else if(controlPoints.size()==4)
    {
        for (float t = 0;t < 1;t = t + 0.01)
        {
            x = (1 - t)*(1 - t)*(1 - t)*controlPoints[0].x() + 3 * t*(1 - t)*(1 - t)*controlPoints[1].x() + 3 * t*t*(1 - t)*controlPoints[2].x() + t*t*t*controlPoints[3].x();
            y = (1 - t)*(1 - t)*(1 - t)*controlPoints[0].y() + 3 * t*(1 - t)*(1 - t)*controlPoints[1].y() + 3 * t*t*(1 - t)*controlPoints[2].y() + t*t*t*controlPoints[3].y();
            aux.push_back(QVector3D(x, y, 0));
        }
    }
    return aux;
}



void Canvas::updateVertexBuffer()
{
    int size = static_cast<int>(_points.size());
    int numberOfBytes = size * static_cast<int>(sizeof(QVector3D));

    glBindBuffer(GL_ARRAY_BUFFER, _pointsBuffer);
    glBufferData(GL_ARRAY_BUFFER, numberOfBytes, _points.data(), GL_STATIC_DRAW);
}



void Canvas::createVAO()
{
    _vao.create();
    _vao.bind();

    //Add vertex.
    glBindBuffer(GL_ARRAY_BUFFER, _pointsBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);
}


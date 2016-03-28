#include <QOpenGLShader>
#include "shaderthingopenglwidget.h"

ShaderThingOpenGLWidget::ShaderThingOpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent), m_shaderProgram(NULL)
{
}

ShaderThingOpenGLWidget::~ShaderThingOpenGLWidget()
{
}

QString ShaderThingOpenGLWidget::compileShader(QString shader)
{
    QOpenGLShader *vertexShader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vertexShader->compileSourceCode(
        "void main()"
        "{"
        "gl_Position = gl_Vertex * gl_ModelViewProjectionMatrix;"
        "}"
    );

    QOpenGLShader *fragmentShader = new QOpenGLShader(QOpenGLShader::Fragment, this);
    if (!fragmentShader->compileSourceCode(shader))
        return fragmentShader->log();

    m_shaderProgram = new QOpenGLShaderProgram(this);
    m_shaderProgram->addShader(vertexShader);
    m_shaderProgram->addShader(fragmentShader);
    if (!m_shaderProgram->link())
        return m_shaderProgram->log();

    startTimer();

    return QString();
}

void ShaderThingOpenGLWidget::initializeGL()
{
    glClearColor(0.1, 0.2, 0.3, 1.0);

    glOrtho(-1.0, 1.0, -1.0, 1.0, 0.1, 10.0);
    glTranslatef(0.0, 0.0, -1.0);
}

void ShaderThingOpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (!m_shaderProgram || !m_shaderProgram->isLinked())
        return;

    m_shaderProgram->bind();
    m_shaderProgram->setUniformValue("time", m_elapsedTime.elapsed() / 1000.0f);
    m_shaderProgram->setUniformValue("resolution", m_resolution);

    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(-1.0, -1.0, 0.0);
    glVertex3f(1.0, -1.0, 0.0);
    glVertex3f(1.0, 1.0, 0.0);
    glVertex3f(-1.0, 1.0, 0.0);
    glEnd();
}

void ShaderThingOpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    m_resolution = QVector2D((float) w, (float) h);
}

void ShaderThingOpenGLWidget::startTimer()
{
    m_timer = new QTimer;
    connect(m_timer, SIGNAL(timeout()), this, SLOT(render()));
    m_timer->start(10);
    m_elapsedTime.start();
}

void ShaderThingOpenGLWidget::render()
{
    update();
}

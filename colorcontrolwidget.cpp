#include "colorcontrolwidget.h"

#include <QPainter>
#include <QPainterPath>
#include <QLabel>
#include <QGraphicsBlurEffect>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPaintEvent>
#include <QImage>


ColorControlWidget::ColorControlWidget(QWidget *parent)
    : QWidget{parent}
{
    setFixedSize(200,300);
    dragPoint = new QLabel(this);
    dragPoint->setFixedSize(5,5);
    // dragPoint->setStyleSheet(
    //     "QLabel{"
    //     "background: white;"
    //     "}"
    //     );

}

void ColorControlWidget::paintEvent(QPaintEvent* ) {

    // QPainter painter(this);
    // QPixmap buffer(size());
    // buffer.fill(Qt::transparent);

    // // 绘制背景和色环
    // painter.fillRect(rect(), QColor(30,30,30));
    // painter.setRenderHint(QPainter::Antialiasing);
    // drawColorWheel(&buffer);

    // QPainter bufferPainter(&buffer);


    // // 绘制拖拽点（白点）
    // bufferPainter.setBrush(Qt::white);
    // bufferPainter.setPen(Qt::NoPen);
    // bufferPainter.drawEllipse(dragPointPos, 3, 3);

    // // 将缓冲区内容绘制到控件
    // painter.drawPixmap(0, 0, buffer);

    QPainter painter(this);


    // 绘制背景和色环
    painter.fillRect(rect(), QColor(30,30,30));
    painter.setRenderHint(QPainter::Antialiasing);
    drawColorWheel(&painter);


    // 绘制拖拽点（白点）
    painter.setBrush(Qt::white);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(dragPointPos, 3, 3);




}

void ColorControlWidget::drawColorWheel(QPixmap* buffer){

    // 更新中心坐标
    center = QPointF(width() / 2, height() / 2);

    // QImage buffer(size(), QImage::Format_RGBA32FPx4_Premultiplied);
    // QPainter painter(&buffer);

    // painter.setRenderHint(QPainter::LosslessImageRendering);

    // QPixmap blurPix(size());
    QPainter painter(buffer);
    painter.setRenderHint(QPainter::Antialiasing);



    // 使用圆锥渐变绘制色调环
    QConicalGradient conicalGrad(center, 0);
    conicalGrad.setColorAt(0.0, Qt::blue);
    conicalGrad.setColorAt(0.166, Qt::magenta);
    conicalGrad.setColorAt(0.333, Qt::red);
    conicalGrad.setColorAt(0.5, Qt::yellow);
    conicalGrad.setColorAt(0.666, Qt::green);
    conicalGrad.setColorAt(0.833, Qt::cyan);
    conicalGrad.setColorAt(1.0, Qt::blue);

    painter.setBrush(conicalGrad);
    painter.drawEllipse(center, radius, radius);



    // //
    // blurPainter.setBrush(conicalGrad);
    // blurPainter.drawEllipse(center, radius, radius);



    // 使用径向渐变调整饱和度（中心白色，边缘透明）
    QRadialGradient radialGrad(center, radius);
    radialGrad.setColorAt(0, Qt::white);
    radialGrad.setColorAt(0.9, Qt::transparent);

    painter.setBrush(radialGrad);
    painter.drawEllipse(center, radius, radius);

    // 变暗
    qreal darkRadius = radius * 0.95;
    QRadialGradient darkGrad(center, darkRadius);

    darkGrad.setColorAt(0, QColor(0, 0, 0, 200));
    darkGrad.setColorAt(1, QColor(0, 0, 0, 220));
    painter.setCompositionMode(QPainter::CompositionMode_Multiply); // 乘法混合模式
    painter.setBrush(darkGrad);
    painter.drawEllipse(center, darkRadius, darkRadius);

    // blurPainter.setCompositionMode(QPainter::CompositionMode_Multiply); // 乘法混合模式
    // blurPainter.setBrush(QColor(0,0,0,255));
    // blurPainter.drawEllipse(center, radius, radius);






    // // 应用模糊效果
    // QPixmap blurredPixmap = applyBlurEffect(blurPix);


    // // 仅在95%半径区域内绘制模糊图像
    // qreal blurAreaRadius = radius * 0.95;
    // QPainterPath clipPath;
    // clipPath.addEllipse(center, blurAreaRadius, blurAreaRadius);
    // painter->setClipPath(clipPath);  // 设置裁剪区域
    // painter->drawPixmap(0,0,blurredPixmap);
    // painter->setClipping(false);     // 重置裁剪状态


    // 十字线
    QPen pen;
    pen.setColor(QColor(255,255,255,200));
    //pen.setWidth(2);
    painter.setPen(pen);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.drawLine(center.x() - radius + 2, center.y(), center.x() + radius - 2, center.y());
    painter.drawLine(center.x(), center.y() - radius + 2, center.x(), center.y() + radius - 2);

    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    // opainter->drawImage(0,0,buffer);
    painter.end();
}

void ColorControlWidget::drawColorWheel(QPainter* painter){

    // 更新中心坐标
    center = QPointF(width() / 2, height() / 2);





    // 使用圆锥渐变绘制色调环
    QConicalGradient conicalGrad(center, 0);
    conicalGrad.setColorAt(0.0, Qt::blue);
    conicalGrad.setColorAt(0.166, Qt::magenta);
    conicalGrad.setColorAt(0.333, Qt::red);
    conicalGrad.setColorAt(0.5, Qt::yellow);
    conicalGrad.setColorAt(0.666, Qt::green);
    conicalGrad.setColorAt(0.833, Qt::cyan);
    conicalGrad.setColorAt(1.0, Qt::blue);

    painter->setBrush(conicalGrad);
    painter->drawEllipse(center, radius, radius);



    // //
    // blurPainter.setBrush(conicalGrad);
    // blurPainter.drawEllipse(center, radius, radius);



    // 使用径向渐变调整饱和度（中心白色，边缘透明）
    QRadialGradient radialGrad(center, radius);
    radialGrad.setColorAt(0, Qt::white);
    radialGrad.setColorAt(0.9, Qt::transparent);

    painter->setBrush(radialGrad);
    painter->drawEllipse(center, radius, radius);

    // 变暗
    qreal darkRadius = radius * 0.95;
    QRadialGradient darkGrad(center, darkRadius);

    darkGrad.setColorAt(0, QColor(0, 0, 0, 200));
    darkGrad.setColorAt(1, QColor(0, 0, 0, 220));
    painter->setCompositionMode(QPainter::CompositionMode_Multiply); // 乘法混合模式
    painter->setBrush(darkGrad);
    painter->drawEllipse(center, darkRadius, darkRadius);

    // blurPainter.setCompositionMode(QPainter::CompositionMode_Multiply); // 乘法混合模式
    // blurPainter.setBrush(QColor(0,0,0,255));
    // blurPainter.drawEllipse(center, radius, radius);






    // // 应用模糊效果
    // QPixmap blurredPixmap = applyBlurEffect(blurPix);


    // // 仅在95%半径区域内绘制模糊图像
    // qreal blurAreaRadius = radius * 0.95;
    // QPainterPath clipPath;
    // clipPath.addEllipse(center, blurAreaRadius, blurAreaRadius);
    // painter->setClipPath(clipPath);  // 设置裁剪区域
    // painter->drawPixmap(0,0,blurredPixmap);
    // painter->setClipping(false);     // 重置裁剪状态


    // 十字线
    QPen pen;
    pen.setColor(QColor(255,255,255,200));
    //pen.setWidth(2);
    painter->setPen(pen);
    painter->setCompositionMode(QPainter::CompositionMode_Source);
    painter->drawLine(center.x() - radius + 2, center.y(), center.x() + radius - 2, center.y());
    painter->drawLine(center.x(), center.y() - radius + 2, center.x(), center.y() + radius - 2);

    painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
    // opainter->drawImage(0,0,buffer);
    // painter->end();
}

// 模糊处理函数
QPixmap ColorControlWidget::applyBlurEffect(const QPixmap &source) {
    QGraphicsBlurEffect *blurEffect = new QGraphicsBlurEffect;
    blurEffect->setBlurRadius(150.0);
    blurEffect->setBlurHints(QGraphicsBlurEffect::QualityHint);

    QGraphicsScene scene;
    QGraphicsPixmapItem item(source);
    item.setGraphicsEffect(blurEffect);
    scene.addItem(&item);

    QPixmap blurred(source.size());
    QPainter painter(&blurred);
    scene.render(&painter);
    return blurred;
}

// resize event
void ColorControlWidget::resizeEvent(QResizeEvent *event){
    QWidget::resizeEvent(event);
    dragPoint->move(rect().center());
    dragPointPos = rect().center(); // 初始化为中心点
    setAttribute(Qt::WA_OpaquePaintEvent, false); // 启用双缓冲
}

// mouseEvent
void ColorControlWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        // 记录鼠标按下的位置
        if(isDragPointInColorWheel(event)){
            pressedPos = event->pos();
            dragPointPos = dragPoint->pos();
            isDragging = true;
        }



    }
}

void ColorControlWidget::mouseMoveEvent(QMouseEvent *event) {
    QPoint delta = (event->pos() - pressedPos).toPoint();
    dragPointPos = pressedPos.toPoint() + delta; // 直接更新坐标
    dragPointPos = QPoint(
        qBound(0, dragPointPos.x(), width()),
        qBound(0, dragPointPos.y(), height())
        );
    offset = resolveColorOffset(dragPointPos);
    update(); // 触发重绘，使用双缓冲避免闪烁
    emit dragPointChange();
}

void ColorControlWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        isDragging = false;
    }
}

bool ColorControlWidget::isDragPointInColorWheel(QMouseEvent *event){
    double dx = event->pos().x() - center.x();
    double dy = event->pos().y() - center.y();
    double dis = std::sqrt(dx * dx + dy * dy);
    if(dis <= radius) return true;
    else return false;
}

ColorOffset ColorControlWidget::resolveColorOffset(QPointF pos){
    double dx = pos.x() - center.x();
    double dy = pos.y() - center.y();
    qDebug() << dx << dy;
    QVector2D posV(dx,dy);
    const QVector2D redV(-0.5, -std::sqrt(3)/2);
    const QVector2D greenV(-0.5, std::sqrt(3)/2);
    const QVector2D blueV(1, 0);
    // red offset
    double redLen = projectLenth(posV, redV);
    double greenLen = projectLenth(posV, greenV);
    double blueLen = projectLenth(posV, blueV);

    return ColorOffset(redLen/radius, greenLen/radius, blueLen/radius);
}
double ColorControlWidget::projectLenth(const QVector2D &a, const QVector2D &b) {
    // 计算点积
    double dotProduct = QVector2D::dotProduct(a, b);

    // 计算投影系数
    double projectionFactor = dotProduct;

    return projectionFactor;
}


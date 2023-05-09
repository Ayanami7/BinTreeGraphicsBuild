#include <QtWidgets/QApplication>
#include "MainWindow.h"

int main(int argc, char* argv[])
{
	//确保缩放属性正确
	QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::Floor);
	QApplication a(argc, argv);

	MainWindow w;
	w.show();

	return a.exec();
}

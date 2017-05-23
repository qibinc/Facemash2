#include "mainwindow.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QFile File("style.qss");
	File.open(QFile::ReadOnly);
	QString StyleSheet = QLatin1String(File.readAll());
	qApp->setStyleSheet(StyleSheet);

	client::MainWindow w;
	w.show();

	return a.exec();
}

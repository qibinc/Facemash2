#include "include/widget.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	Widget w;
	w.setGeometry(500, 200, 320, 240);
	w.show();

	return a.exec();
}

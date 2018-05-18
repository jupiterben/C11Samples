#include <qapplication.h>
#include <qpushButton.h>
#include <qfont>
#include <qwidget>
#include <vector>
std::vector<int, std::allocator<int> > v;

int main(int argc, char *argv[])
{
        QApplication app(argc, argv);
        QWidget window;
        window.resize(400, 300);
        QPushButton quit("Quit", &window);
        //A child is born. 
        //This QPushButton is created with a parent widget (window). 
        //A child widget is always displayed within its parent's area
        quit.setFont(QFont("Times", 18, QFont::Bold));
        quit.setGeometry(210, 250, 180, 40);
        //The result is a button that extends 
        //from position (210, 250) to
        //position (210+180, 250+40).
        QObject::connect(&quit, SIGNAL(clicked()), &app, SLOT(quit()));
        window.show();
        //When a parent widget is shown, it will call show for all its children
        return app.exec();
}

#include <QtSql/QSqlDatabase>
#include <QCoreApplication>
#include <QtDebug>
#include <QtWidgets/QWidget>
#include <QtSql/QSqlQuery>
#include <vtkBMPReader.h>
#include <vtkSmartPointer.h>
#include <vtkImageActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <QVTKWidget.h>

int main(int &argc, char **argv)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("vtk_pic");
    db.setUserName("root");
    db.setPassword("dahuaidan");
    if(!db.open())
    {
        qDebug()<<"open error";
        return 0;
    }

    QSqlQuery query;

    query.exec("Select * from pic_table where ID = 2");

    while(query.next())
    {
        qDebug()<<query.value(2).toString()+"'\'"+query.value(1).toString();
        vtkSmartPointer<vtkBMPReader> reader = vtkSmartPointer<vtkBMPReader>::New();
        reader->SetFileName((query.value(2).toString()+"/"+query.value(1).toString()).toStdString().c_str());
        reader->Update();

        vtkSmartPointer<vtkImageActor> actor = vtkSmartPointer<vtkImageActor>::New();
        actor->SetInputData(reader->GetOutput());

        vtkSmartPointer<vtkRenderer> render = vtkSmartPointer<vtkRenderer>::New();
        render->SetBackground(0.7,0.7,0.7);
        render->AddActor(actor);

        vtkSmartPointer<vtkRenderWindow> window = vtkSmartPointer<vtkRenderWindow>::New();
        window->SetSize(600,480);
        window->AddRenderer(render);
        window->Render();

        vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
        interactor->SetRenderWindow(window);

        vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();
        interactor->SetInteractorStyle(style);
        interactor->Start();
    }
    return EXIT_SUCCESS;
}

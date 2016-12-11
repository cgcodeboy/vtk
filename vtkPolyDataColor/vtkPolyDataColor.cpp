#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkActor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyData.h>
#include <vtkPolygon.h>
#include <vtkPoints.h>
#include <vtkPointData.h>
#include <vtkCellData.h>
#include <vtkTriangle.h>
#include <vtkCellArray.h>
#include <vtkIntArray.h>
#include <vtkLookupTable.h>

int main()
{
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    points->InsertNextPoint(0.0, 0.0, 0.0);
    points->InsertNextPoint(1.0, 0.0, 0.0);
    points->InsertNextPoint(1.0, 1.0, 0.0);
    points->InsertNextPoint(0.0, 1.0, 0.0);
    points->InsertNextPoint(2.0, 0.0, 0.0);

    vtkSmartPointer<vtkPolygon> polygon = vtkSmartPointer<vtkPolygon>::New();
    polygon->GetPointIds()->SetNumberOfIds(4);
    polygon->GetPointIds()->SetId(0,0);
    polygon->GetPointIds()->SetId(1,1);
    polygon->GetPointIds()->SetId(2,2);
    polygon->GetPointIds()->SetId(3,3);

    vtkSmartPointer<vtkTriangle> triangle = vtkSmartPointer<vtkTriangle>::New();
    triangle->GetPointIds()->SetId(0,1);
    triangle->GetPointIds()->SetId(1,2);
    triangle->GetPointIds()->SetId(2,4);

    vtkSmartPointer<vtkCellArray> array = vtkSmartPointer<vtkCellArray>::New();
    array->InsertNextCell(polygon);
    array->InsertNextCell(triangle);

    vtkSmartPointer<vtkPolyData> poly = vtkSmartPointer<vtkPolyData>::New();
    poly->SetPoints(points);
    poly->SetPolys(array);

    unsigned char red[3] = {255,0,0};
    unsigned char green[3] = {0,255,0};
    unsigned char blue[3] = {0,0,255};

    vtkSmartPointer<vtkUnsignedCharArray> pointsColor = vtkSmartPointer<vtkUnsignedCharArray>::New();
    pointsColor->SetNumberOfComponents(3);
    pointsColor->InsertNextTupleValue(red);
    pointsColor->InsertNextTupleValue(green);
    pointsColor->InsertNextTupleValue(blue);
    pointsColor->InsertNextTupleValue(green);
    pointsColor->InsertNextTupleValue(red);
    poly->GetPointData()->SetScalars(pointsColor);

    vtkSmartPointer<vtkUnsignedCharArray> cellsColor = vtkSmartPointer<vtkUnsignedCharArray>::New();
    cellsColor->SetNumberOfComponents(3);
    cellsColor->InsertNextTupleValue(red);
    cellsColor->InsertNextTupleValue(green);
    poly->GetCellData()->SetScalars(cellsColor);

    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(poly);

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    vtkSmartPointer<vtkRenderer> render = vtkSmartPointer<vtkRenderer>::New();
    render->AddActor(actor);
    render->SetBackground(0.7,0.7,0.7);

    vtkSmartPointer<vtkRenderWindow> window = vtkSmartPointer<vtkRenderWindow>::New();
    window->SetSize(600,480);
    window->AddRenderer(render);
    window->Render();

    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(window);

    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    interactor->SetInteractorStyle(style);
    interactor->Start();

    return EXIT_SUCCESS;
}

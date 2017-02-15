#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkPolyData.h>
#include <vtkDataSetMapper.h>
#include <vtkPointPicker.h>
#include <vtkIdTypeArray.h>
#include <vtkSelectionNode.h>
#include <vtkSelection.h>
#include <vtkDataSet.h>
#include <vtkProperty.h>
#include <vtkExtractSelection.h>
#include <vtkRendererCollection.h>
#include <vtkObjectFactory.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>

class PointPicker:public vtkInteractorStyleTrackballCamera
{
public:
    static PointPicker *New();
    vtkTypeMacro(PointPicker, vtkInteractorStyleTrackballCamera)

//    PointPicker()
//    {
//        selectedMapper = vtkSmartPointer<vtkDataSetMapper>::New();
//        selectedActor = vtkSmartPointer<vtkActor>::New();
//    }

    virtual void OnLeftButtonDown()
    {
        this->Interactor->GetPicker()->Pick(this->GetInteractor()->GetEventPosition()[0],\
                this->GetInteractor()->GetEventPosition()[1],\
                0,this->Interactor->GetRenderWindow()\
                ->GetRenderers()->GetFirstRenderer());

        double pos[3];
        this->Interactor->GetPicker()->GetPickPosition(pos);

        vtkSmartPointer<vtkSphereSource> sphere = vtkSmartPointer<vtkSphereSource>::New();
        sphere->Update();

        vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        mapper->SetInputData(sphere->GetOutput());

        vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
        actor->SetMapper(mapper);
        actor->GetProperty()->SetColor(0.6,0.7,0.8);
        actor->SetPosition(pos);
        actor->SetScale(0.2);

        this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(actor);

        //父类的方法需要执行
        vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
    }

private:
//    vtkSmartPointer<vtkDataSetMapper> selectedMapper;
//    vtkSmartPointer<vtkActor> selectedActor;
};

vtkStandardNewMacro(PointPicker)

int main()
{
    vtkSmartPointer<vtkSphereSource> sphere = vtkSmartPointer<vtkSphereSource>::New();
    sphere->SetRadius(5);
    sphere->SetPhiResolution(10);
    sphere->SetThetaResolution(10);
    sphere->Update();

    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(sphere->GetOutput());

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(0.5,0.6,0.7);

    vtkSmartPointer<vtkRenderer> render = vtkSmartPointer<vtkRenderer>::New();
    render->AddActor(actor);
    render->SetBackground(0.8,0.8,0.8);

    vtkSmartPointer<vtkRenderWindow> window = vtkSmartPointer<vtkRenderWindow>::New();
    window->AddRenderer(render);
    window->SetSize(600,480);
    window->Render();

    vtkSmartPointer<vtkPointPicker> picker = vtkSmartPointer<vtkPointPicker>::New();

    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(window);
    interactor->SetPicker(picker);
    interactor->Initialize();

    vtkSmartPointer<PointPicker> style = vtkSmartPointer<PointPicker>::New();
    style->SetDefaultRenderer(render);
    interactor->SetInteractorStyle(style);

    interactor->Start();

    return EXIT_SUCCESS;
}

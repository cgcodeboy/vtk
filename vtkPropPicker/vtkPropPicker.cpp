#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkMath.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkPropPicker.h>
#include <vtkProperty.h>
#include <vtkObjectFactory.h>

class PropPicker:public vtkInteractorStyleTrackballCamera
{
public:
    static PropPicker *New();

    PropPicker()
    {
        lastPickedActor = NULL;
        lastPickedProperty = vtkSmartPointer<vtkProperty>::New();
    }

    virtual void OnLeftButtonDown()
    {
        int *clickPos = this->GetInteractor()->GetEventPosition();
        vtkSmartPointer<vtkPropPicker> picker = vtkSmartPointer<vtkPropPicker>::New();
        picker->Pick(clickPos[0],clickPos[1],0,this->GetDefaultRenderer());
        double *pos = picker->GetPickPosition();
        if(this->lastPickedActor)
        {
            this->lastPickedActor->GetProperty()->DeepCopy(this->lastPickedProperty);
        }
        this->lastPickedActor = picker->GetActor();
        if(this->lastPickedActor)
        {
            this->lastPickedProperty->DeepCopy(this->lastPickedActor->GetProperty());
            this->lastPickedActor->GetProperty()->SetColor(0.8,0.7,0.6);
            this->lastPickedActor->GetProperty()->SetDiffuse(1.0);
            this->lastPickedActor->GetProperty()->SetSpecular(0.0);
        }
        vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
    }

private:
    vtkSmartPointer<vtkActor> lastPickedActor;
    vtkSmartPointer<vtkProperty> lastPickedProperty;
};


vtkStandardNewMacro(PropPicker)

int main()
{
    int numberOfSphere = 10;

    vtkSmartPointer<vtkRenderer> render = vtkSmartPointer<vtkRenderer>::New();
    render->SetBackground(0.8,0.8,0.8);

    vtkSmartPointer<vtkRenderWindow> window = vtkSmartPointer<vtkRenderWindow>::New();
    window->AddRenderer(render);
    window->SetSize(600,480);

    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(window);

    vtkSmartPointer<PropPicker> style = vtkSmartPointer<PropPicker>::New();
    style->SetDefaultRenderer(render);

    interactor->SetInteractorStyle(style);

    for(int i = 0;i<numberOfSphere;i++)
    {
        vtkSmartPointer<vtkSphereSource> source = vtkSmartPointer<vtkSphereSource>::New();
        double x,y,z,radius;
        x = vtkMath::Random(-10,10);
        y = vtkMath::Random(-10,10);
        z = vtkMath::Random(-10,10);
        radius = vtkMath::Random(1,2);
        source->SetRadius(radius);
        source->SetCenter(x,y,z);
        source->SetPhiResolution(15);
        source->SetThetaResolution(15);
        source->Update();

        vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        mapper->SetInputData(source->GetOutput());

        vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
        actor->SetMapper(mapper);
        double r,g,b;
        r = vtkMath::Random(0,1);
        g = vtkMath::Random(0,1);
        b = vtkMath::Random(0,1);
        actor->GetProperty()->SetDiffuseColor(r,g,b);
        actor->GetProperty()->SetDiffuse(0.8);
        actor->GetProperty()->SetSpecular(0.5);
        actor->GetProperty()->SetSpecularColor(1,1,1);
        actor->GetProperty()->SetSpecularPower(32.0);
        render->AddActor(actor);
    }

    window->Render();

    interactor->Start();

    return EXIT_SUCCESS;
}

#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkBMPReader.h>
#include <vtkImageActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkImageMagnify.h>

int main()
{
    vtkSmartPointer<vtkBMPReader> reader = vtkSmartPointer<vtkBMPReader>::New();
    reader->SetFileName("lena.bmp");
    reader->Update();

    vtkSmartPointer<vtkImageMagnify> magnify = vtkSmartPointer<vtkImageMagnify>::New();
    magnify->SetInputConnection(reader->GetOutputPort());
    magnify->SetMagnificationFactors(20,20,1);
    magnify->Update();

    int originalDims[3];
    reader->GetOutput()->GetDimensions(originalDims);

    double originalSpace[3];
    reader->GetOutput()->GetSpacing(originalSpace);

    int shrinkDims[3];
    magnify->GetOutput()->GetDimensions(shrinkDims);

    double shrinkSpace[3];
    magnify->GetOutput()->GetSpacing(shrinkSpace);

    std::cout<<"原图图像维数      ："<<originalDims[0] << " "<<originalDims[1]<<" "<<originalDims[2]<<std::endl;
    std::cout<<"原图图像像素间隔  ："<<originalSpace[0] << " "<<originalSpace[1]<<" "<<originalSpace[2]<<std::endl;
    std::cout<<"重采样图像维数    ："<<shrinkDims[0] << " "<<shrinkDims[1]<<" "<<shrinkDims[2]<<std::endl;
    std::cout<<"重采样图像像素间隔："<<shrinkSpace[0] << " "<<shrinkSpace[1]<<" "<<shrinkSpace[2]<<std::endl;


    vtkSmartPointer<vtkImageActor> originactor = vtkSmartPointer<vtkImageActor>::New();
    originactor->SetInputData(reader->GetOutput());

    vtkSmartPointer<vtkRenderer> originrender = vtkSmartPointer<vtkRenderer>::New();
    originrender->AddActor(originactor);
    originrender->SetBackground(0.8,0.8,0.8);
    originrender->SetViewport(0,0,0.5,1);

    vtkSmartPointer<vtkImageActor> magnifyactor = vtkSmartPointer<vtkImageActor>::New();
    magnifyactor->SetInputData(magnify->GetOutput());

    vtkSmartPointer<vtkRenderer> magnifyrender = vtkSmartPointer<vtkRenderer>::New();
    magnifyrender->AddActor(magnifyactor);
    magnifyrender->SetBackground(0.8,0.8,0.8);
    magnifyrender->SetViewport(0.5,0,1,1);

    vtkSmartPointer<vtkRenderWindow> window = vtkSmartPointer<vtkRenderWindow>::New();
    window->AddRenderer(magnifyrender);
    window->AddRenderer(originrender);
    window->SetSize(600,480);
    window->Render();

    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(window);

    vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();
    interactor->SetInteractorStyle(style);

    interactor->Start();

    return EXIT_SUCCESS;
}

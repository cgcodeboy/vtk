#include <vtkSmartPointer.h>
#include <vtkImageActor.h>
#include <vtkBMPReader.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkImageShrink3D.h>
#include <vtkImageData.h>

#include <iostream>

int main()
{
    vtkSmartPointer<vtkBMPReader> reader = vtkSmartPointer<vtkBMPReader>::New();
    reader->SetFileName("001.bmp");
    reader->Update();

    vtkSmartPointer<vtkImageShrink3D> shrink = vtkSmartPointer<vtkImageShrink3D>::New();
    shrink->SetInputConnection(reader->GetOutputPort());
    shrink->SetShrinkFactors(2,20,1);
    shrink->Update();

    int originalDims[3];
    reader->GetOutput()->GetDimensions(originalDims);

    double originalSpace[3];
    reader->GetOutput()->GetSpacing(originalSpace);

    int shrinkDims[3];
    shrink->GetOutput()->GetDimensions(shrinkDims);

    double shrinkSpace[3];
    shrink->GetOutput()->GetSpacing(shrinkSpace);

    std::cout<<"原图图像维数      ："<<originalDims[0] << " "<<originalDims[1]<<" "<<originalDims[2]<<std::endl;
    std::cout<<"原图图像像素间隔  ："<<originalSpace[0] << " "<<originalSpace[1]<<" "<<originalSpace[2]<<std::endl;
    std::cout<<"重采样图像维数    ："<<shrinkDims[0] << " "<<shrinkDims[1]<<" "<<shrinkDims[2]<<std::endl;
    std::cout<<"重采样图像像素间隔："<<shrinkSpace[0] << " "<<shrinkSpace[1]<<" "<<shrinkSpace[2]<<std::endl;


    vtkSmartPointer<vtkImageActor> originActor = vtkSmartPointer<vtkImageActor>::New();
    originActor->SetInputData(reader->GetOutput());
    vtkSmartPointer<vtkRenderer> originRender = vtkSmartPointer<vtkRenderer>::New();
    originRender->AddActor(originActor);
    originRender->SetBackground(0.8,0.8,0.8);
    originRender->SetViewport(0,0,0.5,1);

    vtkSmartPointer<vtkImageActor> shrinkActor = vtkSmartPointer<vtkImageActor>::New();
    shrinkActor->SetInputData(shrink->GetOutput());
    vtkSmartPointer<vtkRenderer> shrinkRender = vtkSmartPointer<vtkRenderer>::New();
    shrinkRender->AddActor(shrinkActor);
    shrinkRender->SetBackground(0.8,0.8,0.8);
    shrinkRender->SetViewport(0.5,0,1,1);

    vtkSmartPointer<vtkRenderWindow> window = vtkSmartPointer<vtkRenderWindow>::New();
    window->SetSize(600,480);
    window->AddRenderer(originRender);
    window->AddRenderer(shrinkRender);
    window->Render();

    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(window);

    vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();
    interactor->SetInteractorStyle(style);

    interactor->Start();

    return EXIT_SUCCESS;
}

#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkPolyDataReader.h>
#include <vtkPLYReader.h>
#include <vtkFloatArray.h>
#include <vtkPointData.h>
#include <vtkPolyDataNormals.h>
#include <vtkGlyph3D.h>
#include <vtkArrowSource.h>
#include <vtkSphereSource.h>
#include <vtkMaskPoints.h>
#include <vtkProperty.h>
#include <vtkInteractorStyleTrackballCamera.h>

int main()
{
    vtkSmartPointer<vtkPolyDataReader> reader =
        vtkSmartPointer<vtkPolyDataReader>::New();
    reader->SetFileName("fran_cut.vtk");
    reader->Update();

    vtkSmartPointer<vtkPolyDataNormals> normFilter =
        vtkSmartPointer<vtkPolyDataNormals>::New();
    normFilter->SetInputData(reader->GetOutput());
    normFilter->SetComputePointNormals(1);
    normFilter->SetComputeCellNormals(0);
    normFilter->SetAutoOrientNormals(1);
    normFilter->SetSplitting(0);
    normFilter->Update();

    vtkSmartPointer<vtkMaskPoints> mask =
        vtkSmartPointer<vtkMaskPoints>::New();
    mask->SetInputData(normFilter->GetOutput());
    mask->SetMaximumNumberOfPoints(300);
    mask->RandomModeOn();

    vtkSmartPointer<vtkArrowSource> arrow =
        vtkSmartPointer<vtkArrowSource>::New();

    vtkSmartPointer<vtkGlyph3D> glyph =
        vtkSmartPointer<vtkGlyph3D>::New();
    glyph->SetInputData(mask->GetOutput());
    glyph->SetSourceData(arrow->GetOutput());
    glyph->SetVectorModeToUseNormal();
    glyph->SetScaleFactor(0.01);

    vtkSmartPointer<vtkPolyDataMapper> originMapper =
        vtkSmartPointer<vtkPolyDataMapper>::New();
    originMapper->SetInputData(reader->GetOutput());

    vtkSmartPointer<vtkActor> originActor =
        vtkSmartPointer<vtkActor>::New();
    originActor->SetMapper(originMapper);

    vtkSmartPointer<vtkPolyDataMapper> normedMapper =
        vtkSmartPointer<vtkPolyDataMapper>::New();
    normedMapper->SetInputData(normFilter->GetOutput());

    vtkSmartPointer<vtkActor> normedActor =
        vtkSmartPointer<vtkActor>::New();
    normedActor->SetMapper(normedMapper);

    vtkSmartPointer<vtkPolyDataMapper> glyphMapper =
        vtkSmartPointer<vtkPolyDataMapper>::New();
    glyphMapper->SetInputData(glyph->GetOutput());

    vtkSmartPointer<vtkActor> glyphActor =
        vtkSmartPointer<vtkActor>::New();
    glyphActor->SetMapper(glyphMapper);
    glyphActor->GetProperty()->SetColor(0.6, 0.7,0.8);

    double originalViewport[4] = {0.0, 0.0, 0.33, 1.0};
    double normViewport[4] = {0.33, 0.0, 0.66, 1.0};
    double glphViewport[4] = {0.66, 0.0, 1.0, 1.0};

    vtkSmartPointer<vtkRenderer> originalRenderer =
        vtkSmartPointer<vtkRenderer>::New();
    originalRenderer->SetViewport(originalViewport);
    originalRenderer->AddActor(originActor);
    originalRenderer->ResetCamera();
    originalRenderer->SetBackground(1.0, 1.0, 1.0);

    vtkSmartPointer<vtkRenderer> normedRenderer =
        vtkSmartPointer<vtkRenderer>::New();
    normedRenderer->SetViewport(normViewport);
    normedRenderer->AddActor(normedActor);
    normedRenderer->ResetCamera();
    normedRenderer->SetBackground(1.0, 1.0, 1.0);

    vtkSmartPointer<vtkRenderer> glyphRenderer =
        vtkSmartPointer<vtkRenderer>::New();
    glyphRenderer->SetViewport(glphViewport);
    glyphRenderer->AddActor(glyphActor);
    glyphRenderer->AddActor(normedActor);
    glyphRenderer->ResetCamera();
    glyphRenderer->SetBackground(1.0, 1.0, 1.0);

    vtkSmartPointer<vtkRenderWindow> renderWindow =
        vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(originalRenderer);
    renderWindow->AddRenderer(normedRenderer);
    renderWindow->AddRenderer(glyphRenderer);
    renderWindow->SetSize(640, 320);
    renderWindow->Render();
    renderWindow->SetWindowName("PolyDataNormal");

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    vtkSmartPointer<vtkInteractorStyleTrackballCamera> trackball = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    renderWindowInteractor->SetInteractorStyle(trackball);
    renderWindowInteractor->Start();

    return EXIT_SUCCESS;
}

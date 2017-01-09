#include "../MyVtkWindow.h"
#include <vtkSphereSource.h>
#include <vtkIdTypeArray.h>
#include <vtkSelectionNode.h>
#include <vtkSelection.h>
#include <vtkExtractSelection.h>
#include <vtkDataSetSurfaceFilter.h>
#include <vtkProperty.h>
#include <vtkInformation.h>
#include <vtkPolyDataMapper.h>
#include <vtkFeatureEdges.h>
#include <vtkFillHolesFilter.h>
#include <vtkPolyDataNormals.h>
#include <vtkPolyData.h>

int main()
{
    vtkSmartPointer<vtkSphereSource> source = vtkSmartPointer<vtkSphereSource>::New();
    source->SetRadius(10);
    source->Update();

    vtkSmartPointer<vtkIdTypeArray> idarray = vtkSmartPointer<vtkIdTypeArray>::New();
    idarray->SetNumberOfComponents(1);
    idarray->InsertNextValue(2);
//    idarray->InsertNextValue(2);
//    idarray->InsertNextValue(3);
//    idarray->InsertNextValue(4);
//    idarray->InsertNextValue(5);
    idarray->InsertNextValue(10);

    vtkSmartPointer<vtkSelectionNode> selectionNode = vtkSmartPointer<vtkSelectionNode>::New();
    selectionNode->SetFieldType(vtkSelectionNode::CELL);
    selectionNode->SetContentType(vtkSelectionNode::INDICES);
    selectionNode->SetSelectionList(idarray);
    selectionNode->GetProperties()->Set(vtkSelectionNode::INVERSE(),1);

    vtkSmartPointer<vtkSelection> selection = vtkSmartPointer<vtkSelection>::New();
    selection->AddNode(selectionNode);

    vtkSmartPointer<vtkExtractSelection> extractSelection = vtkSmartPointer<vtkExtractSelection>::New();
    extractSelection->SetInputData(0,source->GetOutput());
    extractSelection->SetInputData(1,selection);
    extractSelection->Update();

    vtkSmartPointer<vtkDataSetSurfaceFilter> surfaceFilter = vtkSmartPointer<vtkDataSetSurfaceFilter>::New();
    surfaceFilter->SetInputConnection(extractSelection->GetOutputPort());
    surfaceFilter->Update();

    vtkSmartPointer<vtkPolyData> data = vtkSmartPointer<vtkPolyData>::New();
    data->ShallowCopy(surfaceFilter->GetOutput());

    vtkSmartPointer<vtkPolyDataMapper> originmapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    originmapper->SetInputData(data);

    vtkSmartPointer<vtkActor> originactor = vtkSmartPointer<vtkActor>::New();
    originactor->SetMapper(originmapper);

    vtkSmartPointer<vtkRenderer> originRender = vtkSmartPointer<vtkRenderer>::New();
    originRender->AddActor(originactor);
    originRender->SetBackground(0.7,0.6,0.5);

    vtkSmartPointer<vtkFeatureEdges> featureEdge = vtkSmartPointer<vtkFeatureEdges>::New();
    featureEdge->SetInputData(data);
    featureEdge->BoundaryEdgesOn();
    featureEdge->FeatureEdgesOff();
    featureEdge->ManifoldEdgesOn();
    featureEdge->NonManifoldEdgesOff();
    featureEdge->Update();

    vtkSmartPointer<vtkPolyDataMapper> featureMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    featureMapper->SetInputData(featureEdge->GetOutput());

    vtkSmartPointer<vtkActor> featureActor = vtkSmartPointer<vtkActor>::New();
    featureActor->SetMapper(featureMapper);
    featureActor->GetProperty()->SetDiffuseColor(0.4,0.3,0.3);

    vtkSmartPointer<vtkRenderer> featureRender = vtkSmartPointer<vtkRenderer>::New();
    featureRender->AddActor(featureActor);
    featureRender->AddActor(originactor);
    featureRender->SetBackground(0.5,0.6,0.7);

    vtkSmartPointer<vtkFillHolesFilter> fillFilter = vtkSmartPointer<vtkFillHolesFilter>::New();
    fillFilter->SetInputData(data);
    fillFilter->Update();

    vtkSmartPointer<vtkPolyDataNormals> normal = vtkSmartPointer<vtkPolyDataNormals>::New();
    normal->SetInputConnection(fillFilter->GetOutputPort());
    normal->ConsistencyOn();
    normal->SplittingOff();
    normal->Update();

    vtkSmartPointer<vtkPolyDataMapper> fillMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    fillMapper->SetInputData(normal->GetOutput());

    vtkSmartPointer<vtkActor> fillactor = vtkSmartPointer<vtkActor>::New();
    fillactor->SetMapper(fillMapper);
    fillactor->GetProperty()->SetDiffuseColor(0.2,0.2,0.9);

    vtkSmartPointer<vtkRenderer> fillrender = vtkSmartPointer<vtkRenderer>::New();
    fillrender->AddActor(fillactor);
    fillrender->SetBackground(0.6,0.6,0.6);

    featureRender->SetActiveCamera(originRender->GetActiveCamera());
    fillrender->SetActiveCamera(originRender->GetActiveCamera());

    MyVtkWindow *window = new MyVtkWindow;
    window->addRenderer(originRender);
    window->addRenderer(featureRender);
    window->addRenderer(fillrender);
    window->startRenderWindow();

    return EXIT_SUCCESS;
}

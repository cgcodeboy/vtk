#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkProperty2D.h>
#include <vtkFieldData.h>
#include <vtkLegendBoxActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkDataObject.h>
#include <vtkJPEGReader.h>
#include <vtkBarChartActor.h>
#include <vtkImageAccumulate.h>
#include <vtkIntArray.h>

int main()
{
	vtkSmartPointer<vtkJPEGReader> reader = vtkSmartPointer<vtkJPEGReader>::New();
	reader->SetFileName("003.jpg");
	reader->Update();

	int bins = 16;
	int comps = 3;

	vtkSmartPointer<vtkImageAccumulate> accumulate = vtkSmartPointer<vtkImageAccumulate>::New();
	accumulate->SetInputConnection(reader->GetOutputPort());
	accumulate->SetComponentExtent(0, bins - 1, 0, bins - 1, 0, bins - 1);
	accumulate->SetComponentOrigin(0, 0, 0);
	accumulate->SetComponentSpacing(256.0 / bins, 256.0 / bins, 256.0 / bins);
	accumulate->Update();

	int *output = static_cast<int*>(accumulate->GetOutput()->GetScalarPointer());
	vtkSmartPointer<vtkIntArray> array = vtkSmartPointer<vtkIntArray>::New();
	array->SetNumberOfComponents(1);
	for (int i = 0; i < bins; i++)
	{
		for (int j = 0; j < comps; j++)
		{
			array->InsertNextTuple1(*output++);
		}
	}

	vtkSmartPointer<vtkDataObject> object = vtkSmartPointer<vtkDataObject>::New();
	object->GetFieldData()->AddArray(array);

	vtkSmartPointer<vtkBarChartActor> bar = vtkSmartPointer<vtkBarChartActor>::New();
	bar->SetInput(object);
	bar->GetPositionCoordinate()->SetValue(0.05, 0.05,0.0);
	bar->GetPosition2Coordinate()->SetValue(0.95, 0.95, 0.0);
	bar->GetProperty()->SetColor(0.2, 0.3, 0.4);
	bar->GetLegendActor()->SetNumberOfEntries(object->GetFieldData()->GetArray(0)->GetNumberOfTuples());
	bar->LegendVisibilityOff();
	bar->LabelVisibilityOff();

	double colors[3][3] = {
		{ 1, 0, 0 },
		{ 0, 1, 0 },
		{ 0, 0, 1 } };

	int count = 0;
	for (int i = 0; i < bins; ++i)
	{
		for (int j = 0; j < comps; ++j)
		{
			bar->SetBarColor(count++, colors[j]);
		}
	}

	vtkSmartPointer<vtkRenderer> render = vtkSmartPointer<vtkRenderer>::New();
	render->AddActor(bar);
	render->SetBackground(0.7, 0.7, 0.7);
	
	vtkSmartPointer<vtkRenderWindow> window = vtkSmartPointer<vtkRenderWindow>::New();
	window->AddRenderer(render);
	window->SetSize(640, 480);
	window->Render();

	vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetRenderWindow(window);

	interactor->Start();
	return EXIT_SUCCESS;
}
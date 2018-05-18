

// #include "vtkAutoInit.h"
// VTK_MODULE_INIT(vtkRenderingOpenGL);
// VTK_MODULE_INIT(vtkInteractionStyle);
// VTK_MODULE_INIT(vtkRenderingFreeType);


#include <vtkConeSource.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>
#include <vtkTextMapper.h>
#include "vtkInteractorStyle.h"
#include "vtkCallbackCommand.h"

#include <string>
#include <algorithm>

#define vtkNew(T)  vtkSmartPointer<T>::New()

vtkSmartPointer<vtkActor2D> actor2d;
vtkSmartPointer<vtkTextMapper> textMapper; 
vtkSmartPointer<vtkTextActor> text2d;
vtkSmartPointer<vtkRenderWindow> renderWindow;

void func(vtkObject*, unsigned long eid, void* clientdata, void *calldata)
{
	static int iState = 1;
	iState++;
	textMapper->SetInput(iState%2?"H13":"H11");
	text2d->SetInput(iState % 2 ? "H13" : "H11");
	renderWindow->Render();
}

int main(int, char *[])
{

	textMapper = vtkNew(vtkTextMapper);
	textMapper->SetInput("H12");
	actor2d = vtkNew(vtkActor2D);
	actor2d->SetMapper(textMapper);

	text2d = vtkNew(vtkTextActor);
	text2d->SetInput("s");

    //Create a renderer, render window, and interactor
    auto renderer = vtkNew(vtkRenderer);
    renderWindow = vtkNew(vtkRenderWindow);		
	
	//renderer->AddActor2D(actor2d);
	renderer->AddActor2D(text2d);

    renderWindow->AddRenderer(renderer);

    auto renderWindowInteractor = vtkNew(vtkRenderWindowInteractor);
    renderWindowInteractor->SetRenderWindow(renderWindow);

	auto keypressCallback = vtkNew(vtkCallbackCommand);
	keypressCallback->SetCallback(func);
	renderWindowInteractor->AddObserver(vtkCommand::KeyPressEvent, keypressCallback);
    

    //Render and interact
    renderWindow->Render();
    renderWindowInteractor->Start();

    return EXIT_SUCCESS;
}
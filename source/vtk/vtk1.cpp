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
#include <string>
#include <algorithm>
#include <vtkScaledTextActor.h>

#ifdef WIN32
#define DIR_CHAR '\\'
#else
#define DIR_CHAR '/'
#endif

#define vtkNew(T)  vtkSmartPointer<T>::New()



std::string currentSourceDir()
{
	std::string strFile = __FILE__;
	auto pos = strFile.find_last_of(DIR_CHAR);
	return strFile.substr(0, pos + 1);
}

auto textActorText(int size, int posx, int posy)
{
	auto textActor = vtkNew(vtkTextActor);

	textActor->SetDisplayPosition(posx, posy);
	textActor->SetInput("3D Image");

	auto textProp = textActor->GetTextProperty();
	textProp->SetFontSize(size);
	textProp->SetColor(1, 0, 0);
	textProp->SetFontFamily(VTK_FONT_FILE);

	std::string fontFilePath = currentSourceDir().append("calibri.ttf");
	textProp->SetFontFile(fontFilePath.c_str());

	return textActor;
}

int main(int, char *[])
{
	//Create a cone
	auto  coneSource = vtkNew(vtkConeSource);
	coneSource->Update();

	//Create a mapper and actor
	auto mapper = vtkNew(vtkPolyDataMapper);
	mapper->SetInputConnection(coneSource->GetOutputPort());

	auto actor = vtkNew(vtkActor);
	actor->SetMapper(mapper);

	//Create a renderer, render window, and interactor
	auto renderer = vtkNew(vtkRenderer);

	auto renderWindow = vtkNew(vtkRenderWindow);

	renderWindow->AddRenderer(renderer);

	auto renderWindowInteractor = vtkNew(vtkRenderWindowInteractor);
	renderWindowInteractor->SetRenderWindow(renderWindow);

	//Add the actors to the scenePos
    renderer->AddActor(textActorText(90,10,10));
	renderer->AddActor(textActorText(12, 20, 20));
	renderer->AddActor(textActorText(14,30,30));

	renderer->AddActor(actor);
	renderer->SetBackground(.3, .2, .1); // Background color dark red

	//Render and interact
	renderWindow->Render();
	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}
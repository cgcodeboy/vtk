#ifndef MY_VTK_WINDOW_H
#define MY_VTK_WINDOW_H

#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>

#include <vector>

using namespace std;

class MyVtkWindow{
private:
    vtkSmartPointer<vtkRenderer> m_render;
    vtkSmartPointer<vtkRenderWindow> m_window;
    vtkSmartPointer<vtkRenderWindowInteractor> m_interactor;
    vtkSmartPointer<vtkInteractorStyleTrackballCamera> m_style;

    int windowWidth;
    int windowHeight;

    vector< vtkSmartPointer <vtkActor> > actorVec;
    vector< vtkSmartPointer <vtkRenderer> > renderVec;
public:
    MyVtkWindow()
    {
        this->m_render = vtkSmartPointer<vtkRenderer>::New();
        this->m_window = vtkSmartPointer<vtkRenderWindow>::New();
        this->m_interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
        this->m_style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();

        windowHeight = 240;
        windowWidth = 300;
    }

    void startRenderWindow()
    {
        for(int i = 0;i<actorVec.size();i++)
        {
            m_render->AddActor(actorVec[i]);
        }
        m_render->SetBackground(0.7,0.6,0.8);
        for(int i = 0;i<renderVec.size();i++)
        {
            vtkSmartPointer<vtkRenderer> render = renderVec[i];
            render->SetViewport((float)i/renderVec.size(),0,(float)(i+1)/renderVec.size(),1.0);
            m_window->AddRenderer(render);
        }
        m_window->Render();
        m_window->SetSize(windowWidth*renderVec.size(),windowHeight);
        m_interactor->SetRenderWindow(m_window);
        m_interactor->SetInteractorStyle(m_style);
        m_interactor->Start();
    }

    vtkSmartPointer<vtkRenderWindow> getRenderWindow()
    {
        return this->m_window;
    }

    vtkSmartPointer<vtkRenderWindowInteractor> getInteractor()
    {
        return this->m_interactor;
    }

    vtkSmartPointer<vtkInteractorStyleTrackballCamera> getInteractorStyle()
    {
        return this->m_style;
    }

    void setWindowSize(int width = 600,int height = 480)
    {
        this->windowHeight = height;
        this->windowWidth = width;
    }

    void addActor(vtkSmartPointer<vtkActor> actor)
    {
        this->m_render->AddActor(actor);
        this->actorVec.push_back(actor);
    }

    void addRenderer(vtkSmartPointer<vtkRenderer> render)
    {
        this->m_window->AddRenderer(render);
        this->renderVec.push_back(render);
    }
};

#endif

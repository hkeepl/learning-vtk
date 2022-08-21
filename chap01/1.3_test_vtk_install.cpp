#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <iostream>

int main()
{
    auto ren_win = vtkSmartPointer<vtkRenderWindow>::New();
    ren_win->Render();
    std::cin.get();

    return 0;
}
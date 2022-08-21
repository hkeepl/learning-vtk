#include <vtkDoubleArray.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPointData.h>
#include <vtkDataSetAttributes.h>
#include <iostream>

int main() {
  auto points = vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0, 0, 0);
  points->InsertNextPoint(1, 0, 0);

  auto polydata = vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);

  // 给点数据添加标量值
  auto weights = vtkSmartPointer<vtkDoubleArray>::New();
  weights->SetNumberOfValues(2);
  weights->SetValue(0, 1);
  weights->SetValue(1, 2);
  polydata->GetPointData()->SetScalars(weights);

  auto weight = vtkDoubleArray::SafeDownCast(polydata->GetPointData()->GetScalars())->GetValue(0);
  std::cout << "weight: " << weight << std::endl;
  return 0;
}

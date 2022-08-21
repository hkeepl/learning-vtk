#include <iostream>
#include <vtkFloatArray.h>
#include <vtkSmartPointer.h>

int main() {
  // 创建数组（固定长度）
  {
    auto array = vtkSmartPointer<vtkFloatArray>::New();
    array->SetNumberOfComponents(1);
    array->SetNumberOfTuples(10);
    array->SetComponent(5, 0, 10.0);
    array->SetTuple1(6, 9.0); // 设置元组大小是1的第六个元组

    std::cout << array->GetComponent(5, 0) << " " << array->GetComponent(6, 0) << std::endl;
  }

  // 动态创建
  {
    auto array = vtkSmartPointer<vtkFloatArray>::New();
    array->SetNumberOfComponents(1);
    array->InsertNextTuple1(16);
    array->InsertNextTuple1(42);
    // array->InsertNextTuple2(1, 2); // 错误

    std::cout << array->GetComponent(0, 0) << " " << array->GetComponent(1, 0) << std::endl;
  }
  return 0;
}

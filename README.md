# Laba2
glm::mat4 InitCameraTransform(const glm::vec3& Target, const glm::vec3& Up) // Функция генерации преобразования камеры.

glm::vec3 Normalize(glm::vec3 v) // Для генерации матрицы UVN делаем вектора единичной длины. Все компоненты вектора делятся на его длину.

glm::vec3 Cross(const glm::vec3 v1, const glm::vec3 v2) // Функция возвращает вектор, перпендикулярный плоскости, определяемой исходными векторами.

glm::mat4 InitPerspectiveProj(float fovy, float aspect, float znear, float zfar) // Функция для проецирования перспективы.

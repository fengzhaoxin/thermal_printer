from PIL import Image
import numpy as np
img = Image.open('test.png')
img = img.convert('1')
img_r = img.resize((320,240))
img_arr = np.array(img_r)
img_arr2 = np.packbits(img_arr)
img_new = img_arr2.reshape((240,40))

# 获取数组的形状
rows, cols = img_new.shape

# 将数组转换为C语言的数组字符串
c_array = ',\n'.join(['{' + ', '.join(map(str, row)) + '}' for row in img_new])

# 创建C语言的数组声明和初始化语句
c_code = 'uint8_t array[' + str(rows) + '][' + str(cols) + '] = \n{' + c_array + '};'

# 将C语言的代码写入新的文件
with open('test_img.h', 'w') as f:
    f.write(c_code)

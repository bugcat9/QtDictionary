# 读取GB编码的txt文件内容
with open('txt\\2.txt', 'r', encoding='gbk') as f:
    gbk_content = f.read()

# 将内容转换为UTF-8编码
utf8_content = gbk_content.encode('utf-8')

# 写入UTF-8编码的内容到新文件
with open('output_utf8_file.txt', 'wb') as f:
    f.write(utf8_content)

print("文件转换完成！")
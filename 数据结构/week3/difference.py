# 打开两个文本文件
file1 = open("file1.txt", "r")
file2 = open("file2.txt", "r")

# 逐行读取文件内容
file1_lines = file1.readlines()
file2_lines = file2.readlines()

# 关闭文件
file1.close()
file2.close()

# 比较两个文件的不同之处
line_num = 1
for line1, line2 in zip(file1_lines, file2_lines):
    if line1 != line2:
        print(f"行 {line_num} 不同:")
        print(f"文件1: {line1.strip()}")
        print(f"文件2: {line2.strip()}\n")
    line_num += 1

# 如果其中一个文件还有剩余行，将其打印出来
while line_num <= max(len(file1_lines), len(file2_lines)):
    if line_num <= len(file1_lines):
        print(f"文件1多余行: {file1_lines[line_num-1].strip()}")
    if line_num <= len(file2_lines):
        print(f"文件2多余行: {file2_lines[line_num-1].strip()}")
    line_num += 1

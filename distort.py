import random
from PIL import Image
import io

# heart rate sensor function 

    
def heart_sensor():
    pass

def distort_pass(data):
    start = 500
    end = len(data) - 2
    
    # do a few swaps per pass
    for _ in range(5):
        chunk_size = random.randint(50, 100)
        chunk_start = random.randint(start, end - chunk_size)
        chunk = data[chunk_start : chunk_start + chunk_size]
        paste_at = random.randint(start, end - chunk_size)
        data[paste_at : paste_at + chunk_size] = chunk
    
    return data

def compress_pass(data, quality=15):
    buffer = io.BytesIO(data)
    img = Image.open(buffer)
    out = io.BytesIO()
    img.save(out, format='JPEG', quality=quality)
    return bytearray(out.getvalue())

# Load original
with open('pythondistort6.jpg', 'rb') as f:
    data = bytearray(f.read())

# Run 20 passes, save each generation
for i in range(5):
    data = distort_pass(data)
    data = compress_pass(data)
    with open(f'pass_{i:03d}.jpg', 'wb') as f:
        f.write(data)
    print(f'Pass {i+1} done')
import io
from PIL import Image

image = Image.open("1.jpg")

output = io.BytesIO()
image.save(output, format="JPEG")
data = output.getvalue()

with open("2.jpg", "wb") as f:
    f.write(data)

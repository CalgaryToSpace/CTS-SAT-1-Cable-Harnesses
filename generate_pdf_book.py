# /// script
# dependencies = [
#   "reportlab",
# ]
# ///

import re
from pathlib import Path
from reportlab.lib.pagesizes import letter
from reportlab.pdfgen import canvas
from reportlab.lib.utils import ImageReader

# Settings
images_folder = Path(__file__).parent / "outputs"
output_pdf = Path(__file__).parent / "cable_harnesses.pdf"
images_per_page = 3


def natural_sort_key(path):
    stem = path.stem.split("_")[-1]
    # Separate number and optional letter
    match = re.match(r"(\d+)([A-Za-z]*)", stem)
    if match:
        number_part = int(match.group(1))
        letter_part = match.group(2)
        return (number_part, letter_part)
    else:
        # fallback if doesn't match
        return (0, stem)


# Get image files
image_files = sorted(
    list(images_folder.glob("*.png")),
    key=natural_sort_key,
)

# Constants
PAGE_WIDTH, PAGE_HEIGHT = letter
MARGIN = 36  # half inch margin

# Image display area
usable_height = PAGE_HEIGHT - 2 * MARGIN
image_height = usable_height / images_per_page
image_width = PAGE_WIDTH - 2 * MARGIN

def add_image(c, img_path, position):
    img = ImageReader(img_path)
    iw, ih = img.getSize()
    aspect = iw / ih
    target_height = image_height
    target_width = target_height * aspect
    if target_width > image_width:
        target_width = image_width
        target_height = target_width / aspect

    x = (PAGE_WIDTH - target_width) / 2
    y = PAGE_HEIGHT - MARGIN - (position + 1) * image_height + (image_height - target_height) / 2
    c.drawImage(img, x, y, width=target_width, height=target_height)

# Create the PDF
c = canvas.Canvas(str(output_pdf), pagesize=letter)

for idx, img_file in enumerate(image_files):
    position = idx % images_per_page
    add_image(c, img_file, position)

    # After placing two images, or if it's the last image, add a new page
    if (position == images_per_page - 1) or (idx == len(image_files) - 1):
        c.showPage()

c.save()

print(f"PDF saved to {output_pdf}")

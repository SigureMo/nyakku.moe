from PIL import Image

def imgs2pdf(img_path_list, pdf_path):
    img_01 = Image.open(img_path_list[0])
    img_others = []
    for img_path in img_path_list[1:]:
        img = Image.open(img_path)
        if img.mode == "RGBA":
            img = img.convert('RGB')
            img_others.append(img)
        else:
            img_others.append(img)
    img_01.save(pdf_path, "PDF", resolution=100.0, save_all=True, append_images=img_others)

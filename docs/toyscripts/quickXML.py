# Quickly make an xml with fields from a list. First use-case is for drawio
# jun.allard@uci.edu allardlab.com learns to code!
import xml.etree.cElementTree as ET

with open("items.md") as file:
    items = [line.rstrip() for line in file]

print(items)

root = ET.Element("root")

idStart = 6

for id, item in enumerate(items):
    doc = ET.SubElement(root, "mxCell", id=str(id+idStart), value=item, style="rounded=1;whiteSpace=wrap;html=1;", vertex="1", parent="1")
    ET.SubElement(doc, "mxGeometry", x="140", y="310", width="120", height="30", as_="geometry")


# ET.SubElement(doc, "field1", name="blah").text = "some value1"
# ET.SubElement(doc, "field2", name="asdfasd").text = "some vlaue2"

tree = ET.ElementTree(root)
tree.write("filename.xml")
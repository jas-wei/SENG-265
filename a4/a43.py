"""Assignment 4 Part 3"""
print(__doc__)

from typing import List, NamedTuple
import random
from collections import namedtuple

"""
Part 1
"""

# Define named tuples for shape attributes
# Allows for you to access each tuple index by name, rather than index number
CircleAttrs = namedtuple('CircleAttrs', 'cx cy rad')
RectAttrs = namedtuple('RectAttrs', 'x y width height')
EllipseAttrs = namedtuple('EllipseAttrs', 'cx cy rx ry')

class ColorAttrs(NamedTuple):
    """
    ColorAttrs class
    Attributes for defining a color.
    """
    red: int
    green: int
    blue: int
    op: float

class HtmlComponent:
    """
    HtmlComponent class

    Superclass to render an HTML component. Like an interface so that all children 
    of HtmlComponent implement the render method.
    """
    def render(self) -> str:
        """
        render() method
        base for subclass to impliment render method
        """
        raise NotImplementedError("Subclass must implement render method")

class CircleShape(HtmlComponent):
    """
    CircleShape class
    To create circle objects and render circle elements.
    """
    def __init__(self, cir: CircleAttrs, col: ColorAttrs) -> None:
        """
        __init__() method
        """
        self.cx: int = cir.cx
        self.cy: int = cir.cy
        self.rad: int = cir.rad
        self.red: int = col.red
        self.green: int = col.green
        self.blue: int = col.blue
        self.op: float = col.op
        
    def render(self) -> str:
        """
        render() method
        Render the circle as an SVG element.
        """
        return (f'      <circle cx="{self.cx}" cy="{self.cy}" r="{self.rad}" '
                f'fill="rgb({self.red}, {self.green}, {self.blue})" fill-opacity="{self.op}"></circle>')

class RectangleShape(HtmlComponent):
    """
    RectangleShape class
    To create rectangle objects and render rectangle elements.
    """
    def __init__(self, rect: RectAttrs, col: ColorAttrs) -> None:
        """
        __init__() method
        """
        self.x: int = rect.x
        self.y: int = rect.y
        self.width: int = rect.width
        self.height: int = rect.height
        self.red: int = col.red
        self.green: int = col.green
        self.blue: int = col.blue
        self.op: float = col.op

    def render(self) -> str:
        """
        render() method
        Render the rectangle as an SVG element.
        """
        return (f'      <rect x="{self.x}" y="{self.y}" width="{self.width}" height="{self.height}" '
                f'fill="rgb({self.red}, {self.green}, {self.blue})" fill-opacity="{self.op}"></rect>')

class EllipseShape(HtmlComponent):
    """
    EllipseShape class
    To create ellipse objects and render elliipse elements.
    """
    def __init__(self, ell: EllipseAttrs, col: ColorAttrs) -> None:
        """
        __init__() method
        """
        self.cx: int = ell.cx
        self.cy: int = ell.cy
        self.rx: int = ell.rx
        self.ry: int = ell.ry
        self.red: int = col.red
        self.green: int = col.green
        self.blue: int = col.blue
        self.op: float = col.op

    def render(self) -> str:
        """
        render() method
        Render the ellipse as an SVG element.
        """
        return (f'<ellipse cx="{self.cx}" cy="{self.cy}" rx="{self.rx}" ry="{self.ry}" '
                f'fill="rgb({self.red}, {self.green}, {self.blue})" fill-opacity="{self.op}"></ellipse>')

class SvgCanvas(HtmlComponent):
    """
    SvgCanvas class
    To generate the <svg>, </svg> tags for generating SVG code in an SVG canvas or viewport
    """
    def __init__(self, width: int, height: int) -> None:
        """
        __init__() method
        """
        self.width: int = width
        self.height: int = height
        self.elements: List[HtmlComponent] = []

    def add_element(self, element: HtmlComponent) -> None:
        """
        add_element() method
        adds an HtmlComponent shape to object's element list  
        """
        self.elements.append(element)

    def gen_art(self) -> None:
        """
        gen_art() method
        Generate art (circles) in the SVG canvas.
        Adds circle instances into the elements list.
        """
        self.add_element(CircleShape(CircleAttrs(50, 50, 50), ColorAttrs(255, 0, 0, 1.0)))
        self.add_element(CircleShape(CircleAttrs(150, 50, 50), ColorAttrs(255, 0, 0, 1.0)))
        self.add_element(CircleShape(CircleAttrs(250, 50, 50), ColorAttrs(255, 0, 0, 1.0)))
        self.add_element(CircleShape(CircleAttrs(350, 50, 50), ColorAttrs(255, 0, 0, 1.0)))
        self.add_element(CircleShape(CircleAttrs(450, 50, 50), ColorAttrs(255, 0, 0, 1.0)))
        self.add_element(CircleShape(CircleAttrs(50, 250, 50), ColorAttrs(0, 0, 255, 1.0)))
        self.add_element(CircleShape(CircleAttrs(150, 250, 50), ColorAttrs(0, 0, 255, 1.0)))
        self.add_element(CircleShape(CircleAttrs(250, 250, 50), ColorAttrs(0, 0, 255, 1.0)))
        self.add_element(CircleShape(CircleAttrs(350, 250, 50), ColorAttrs(0, 0, 255, 1.0)))
        self.add_element(CircleShape(CircleAttrs(450, 250, 50), ColorAttrs(0, 0, 255, 1.0)))

    def render(self) -> str:
        """
        render() method
        Render the SVG canvas with all its elements.
        """
        #render each element(shape) from element list into one giant string
        elements_html = "\n".join(
            element.render()
            for element in self.elements
        )

        #svg canvas
        svg_html = (
            f'<svg width="{self.width}" height="{self.height}">\n'
            f'{elements_html}\n'
            f'      </svg>'
        )
        
        return svg_html

class HtmlDocument:
    """
    HtmlDocument class
    Develop a Python class called HtmlDocument to generate an HTML page consisting of a header and a body.
    """
    def __init__(self, title: str) -> None:
        """
        __init__() method
        """
        self.title: str = title
        self.header_content: str = ""
        self.body_content: str = ""
        self.comment: str = ""

    def set_header(self, content: str) -> None:
        """
        set_header() method
        sets the header field
        """
        self.header_content = content

    def add_to_body(self, content: str) -> None:
        """
        add_to_body() method
        adds extra content to body field
        """
        self.body_content += content

    def add_svg_canvas(self, canvas: SvgCanvas) -> None:
        """
        add_svg_canvas() method
        adds extra content to body field
        """
        self.body_content += canvas.render()

    def write_HTML_comment(self, tab_times: int, com: str) -> None:
        """
        write_HTML_comment() method
        Write HTML comment.
        """
        tab: str = " " * tab_times
        self.comment = f"{tab}<!--{com}-->\n"

    def generate_html(self) -> str:
        """
        generate_html() method
        Generate the complete HTML document.
        """
        html = (f"<!DOCTYPE html>\n"
                f"<html>\n"
                f"<head>\n"
                f"  <title>{self.title}</title>\n"
                f"</head>\n"
                f"<body>\n"
                f"{self.comment}"
                f"  {self.body_content}\n"
                f"</body>\n"
                f"</html>\n")
        return html

def write_html_file(file_name: str, html_content: str) -> None:
    """
    write_html_file() method
    Write the generated HTML content to an HTML file.
    """
    with open(file_name, "w") as f:
        f.write(html_content)

def part1() -> None:
    """
    part1() method
    Create and save the HTML document for part 1.
    """
    doc = HtmlDocument("My Art")

    svg_canvas = SvgCanvas(500, 300)  # width, height
    svg_canvas.gen_art()  # adding circles to elements list
    doc.add_svg_canvas(svg_canvas)
    doc.write_HTML_comment(2, "Define SVG drawing box")

    html_content = doc.generate_html()
    write_html_file("my-Part1-V3-Art.html", html_content)  # save to file

"""
Part 2
"""

class PyArtConfig:
    """
    PyArtConfig class
    configures the ranges of values html elements can use 
    """
    # Default ranges as class variables
    SHA_RANGE = (0, 2)
    X_RANGE = (0, 500)
    Y_RANGE = (0, 500)
    RAD_RANGE = (0, 100)
    RX_RANGE = (10, 30)
    RY_RANGE = (10, 30)
    W_RANGE = (10, 100)
    H_RANGE = (10, 100)
    R_RANGE = (0, 255)
    G_RANGE = (0, 255)
    B_RANGE = (0, 255)
    OP_RANGE = (0.0, 1.0)

    def __init__(self, **kwargs) -> None:
        """
        __init__() method
        """
        # Initialize ranges with provided values or defaults
        self.sha_range = kwargs.get('sha_range', self.SHA_RANGE)
        self.x_range = kwargs.get('x_range', self.X_RANGE)
        self.y_range = kwargs.get('y_range', self.Y_RANGE)
        self.rad_range = kwargs.get('rad_range', self.RAD_RANGE)
        self.rx_range = kwargs.get('rx_range', self.RX_RANGE)
        self.ry_range = kwargs.get('ry_range', self.RY_RANGE)
        self.w_range = kwargs.get('w_range', self.W_RANGE)
        self.h_range = kwargs.get('h_range', self.H_RANGE)
        self.r_range = kwargs.get('r_range', self.R_RANGE)
        self.g_range = kwargs.get('g_range', self.G_RANGE)
        self.b_range = kwargs.get('b_range', self.B_RANGE)
        self.op_range = kwargs.get('op_range', self.OP_RANGE)

class RandomShape:
    """
    RandomShape class
    Uses the ranges from PyArtConfig to genenate random numbers within each set range. 
    Also keeps track of the object count 
    """
    COUNT = 0
    def __init__(self, config: PyArtConfig) -> None:
        """
        __init__() method
        """
        RandomShape.COUNT += 1
        self.count: int = RandomShape.COUNT
        self.sha: int = random.randint(config.sha_range[0], config.sha_range[1])
        self.x: int = random.randint(config.x_range[0], config.x_range[1])
        self.y: int = random.randint(config.y_range[0], config.y_range[1])
        self.rad: int = random.randint(config.rad_range[0], config.rad_range[1])
        self.rx: int = random.randint(config.rx_range[0], config.rx_range[1])
        self.ry: int = random.randint(config.ry_range[0], config.ry_range[1])
        self.w: int = random.randint(config.w_range[0], config.w_range[1])
        self.h: int = random.randint(config.h_range[0], config.h_range[1])
        self.r: int = random.randint(config.r_range[0], config.r_range[1])
        self.g: int = random.randint(config.g_range[0], config.g_range[1])
        self.b: int = random.randint(config.b_range[0], config.b_range[1])
        self.op: float = round(random.uniform(config.op_range[0], config.op_range[1]), 1)

    def __str__(self) -> str:
        """
        __str__() method
        returns a string containing each field's value
        """
        return (f"Shape {self.count}:\n"
                f"  Type: {self.sha}\n"
                f"  Position: ({self.x}, {self.y})\n"
                f"  Radius: {self.rad}\n"
                f"  Ellipse radii: ({self.rx}, {self.ry})\n"
                f"  Width: {self.w}\n"
                f"  Height: {self.h}\n"
                f"  Color: (R: {self.r}, G: {self.g}, B: {self.b})\n"
                f"  Opacity: {self.op}")

    def as_part2_line(self) -> str:
        """
        as_part2_line() method
        generates tbe body of the radom number table
        """
        return f"{self.count:>3} {self.sha:>3} {self.x:>3} {self.y:>3} {self.rad:>3} {self.rx:>3} {self.ry:>3} {self.w:>3} {self.h:>3} {self.r:>3} {self.g:>3} {self.b:>3} {self.op:>3.1f}"

    def as_svg(self) -> str:
        """
        as_svg() method
        returns the appropriate svg line depending on what the object's shape is
        """
        if self.sha == 0:  # Circle
            return f'<circle cx="{self.x}" cy="{self.y}" r="{self.rad}" fill="rgb({self.r},{self.g},{self.b})" fill-opacity="{self.op}"/>'
        elif self.sha == 1:  # Rectangle
            return f'<rect x="{self.x}" y="{self.y}" width="{self.w}" height="{self.h}" fill="rgb({self.r},{self.g},{self.b})" fill-opacity="{self.op}"/>'
        elif self.sha == 3:  # Ellipse
            return f'<ellipse cx="{self.x}" cy="{self.y}" rx="{self.rx}" ry="{self.ry}" fill="rgb({self.r},{self.g},{self.b})" fill-opacity="{self.op}"/>'
        else:
            return "<!-- Unknown shape -->"
        
def generate_random_shapes(num_shapes: int, config: PyArtConfig) -> None:
    """
    generate_random_shapes() method
    Generate and print table of random shapes with their attributes.
    """
    shapes = [RandomShape(config) for _ in range(num_shapes)]
    print(" CNT SHA  X  Y  RAD  RX  RY   W   H   R   G   B  OP")
    for shape in shapes:
        print(shape.as_part2_line())

def part2() -> None:
    """
    part2() method
    Generate random shapes for part 2.
    """
    config = PyArtConfig()
    generate_random_shapes(10, config)

"""
Part 3
"""

class GreetingCard(HtmlComponent):
    """
    GreetingCard class
    GreetingCard class to render SVG elements.
    """
    def __init__(self, width: int, height: int) -> None:
        """
        __init__() method
        """
        self.width: int = width
        self.height: int = height
        self.elements: List[HtmlComponent] = []

    def add_element(self, element: HtmlComponent) -> None:
        """
        add_element() method
        adds HtmlComponent shape element into the element list
        """
        self.elements.append(element)

    def render(self) -> str:
        """
        render() method
        Render the SVG canvas with all its elements.
        """
        #render each element(shape) from element list into one giant string
        elements_html = "\n".join(
            element.render()
            for element in self.elements
        )
        #svg canvas
        svg_html = (
            f'<svg width="{self.width}" height="{self.height}">\n'
            f'{elements_html}\n'
            f'      </svg>'
        )
        
        return svg_html
    
def configure_elements(greeting: GreetingCard, shape_cap: int, **kwargs) -> None:
    """
    configure_elements() method
    Configure elements in the greeting card.
    """
    #configures a list of random shapes
    config = PyArtConfig(**kwargs)
    shapes = [RandomShape(config) for _ in range(shape_cap)]

    # itterate through the list of random shapes, adding appropriate svg element into the GreetingCard element list depending on shape type
    for shape in shapes:
        if shape.sha == 0:
            element = CircleShape(CircleAttrs(shape.x, shape.y, shape.rad), ColorAttrs(shape.r, shape.g, shape.b, shape.op))
            greeting.add_element(element)
        elif shape.sha == 1:
            element = RectangleShape(RectAttrs(shape.x, shape.y, shape.w, shape.h), ColorAttrs(shape.r, shape.g, shape.b, shape.op))
            greeting.add_element(element)

def configure_greeting_html(greeting: GreetingCard, file: str) -> None:
    """
    configure_html() method
    Configure HTML document with SVG greeting card.
    """
    doc = HtmlDocument("My Art")
    doc.add_svg_canvas(greeting)
    doc.write_HTML_comment(2, "Define SVG drawing box")

    html_content = doc.generate_html()
    write_html_file(file, html_content)

def part3() -> None:
    """
    part3() method
    Generate greeting cards with different configurations for part 3.
    """
    #birthday greeting card
    greeting1 = GreetingCard(500, 500)  # width, height
    configure_elements(greeting1, 200, sha_range=(0, 1), r_range=(100, 255), g_range=(100, 255), b_range=(100, 255),)
    configure_greeting_html(greeting1, "a431.html")
    
    #winter greeting card
    greeting2 = GreetingCard(1000, 600)  # width, height
    configure_elements(greeting2, 1000, sha_range=(0, 0), x_range=(0, 1000), y_range=(0, 600), rad_range=(0, 50), 
                        r_range=(100, 255), g_range=(60, 255), b_range=(200, 255), op_range=(0.0, 0.50))
    configure_greeting_html(greeting2, "a432.html")

    #halloween greeting card
    greeting3 = GreetingCard(1500, 500)  # width, height
    configure_elements(greeting3, 200, x_range=(0, 1500), rad_range=(50, 100), w_range=(10, 100), h_range=(10, 100),
                         r_range=(150, 255), g_range=(100, 220), b_range=(0, 50), op_range=(0.2, 0.70))
    configure_greeting_html(greeting3, "a433.html")

def main() -> None:
    """
    main() method
    Main method to create HTML document with SVG art.
    """
    part3()

if __name__ == "__main__":
    main()
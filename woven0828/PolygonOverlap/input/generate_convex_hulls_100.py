import json
import random

def random_point(center_x, center_y, radius):
    angle = random.uniform(0, 2 * 3.141592653589793)
    r = radius * (0.7 + 0.3 * random.random())
    x = center_x + r * random.uniform(0.9, 1.1) * math.cos(angle)
    y = center_y + r * random.uniform(0.9, 1.1) * math.sin(angle)
    return (x, y)

def generate_polygon(center_x, center_y, radius, num_points=10):
    angles = sorted([random.uniform(0, 2 * 3.141592653589793) for _ in range(num_points)])
    points = []
    for angle in angles:
        r = radius * (0.7 + 0.3 * random.random())
        x = center_x + r * math.cos(angle)
        y = center_y + r * math.sin(angle)
        points.append({"x": x, "y": y})
    return points

import math

polygons = []
random.seed(42)
for i in range(100):
    cx = random.uniform(-40, 40)
    cy = random.uniform(-40, 40)
    radius = random.uniform(3, 10)
    apexes = generate_polygon(cx, cy, radius, 10)
    polygons.append({
        "ID": i,
        "apexes": apexes
    })

data = {"convex hulls": polygons}

with open(r'd:\mygit_code\program\woven0828\PolygonOverlap\input\convex_hulls_100.json', 'w', encoding='utf-8') as f:
    json.dump(data, f, indent=2, ensure_ascii=False)

import json
import random
import math

def generate_polygon(center_x, center_y, radius, num_points=10):
    angles = sorted([random.uniform(0, 2 * math.pi) for _ in range(num_points)])
    points = []
    for angle in angles:
        r = radius * (0.7 + 0.3 * random.random())
        x = center_x + r * math.cos(angle)
        y = center_y + r * math.sin(angle)
        # 保留10位小数
        points.append({"x": round(x, 10), "y": round(y, 10)})
    return points

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
        "apexes": apexes
    })

data = {"convex hulls": polygons}

with open(r'd:\mygit_code\program\woven0828\PolygonOverlap\input\convex_hulls_100.json', 'w', encoding='utf-8') as f:
    json.dump(data, f, indent=2, ensure_ascii=False)

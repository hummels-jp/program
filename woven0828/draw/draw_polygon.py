import matplotlib
matplotlib.use('Agg')  # Force non-interactive backend to ensure images are saved correctly

import matplotlib.pyplot as plt
import matplotlib.patches as patches

def draw_case_1():
    fig, ax = plt.subplots(figsize=(8, 6))
    
    # Draw the clipping window
    rect = patches.Rectangle((-5, -5), 10, 10, linewidth=2, edgecolor='black', facecolor='none')
    ax.add_patch(rect)
    
    # Draw the line segment (Start -> End) completely inside the window
    start = (2, 2)
    end = (4, 4)
    ax.plot([start[0], end[0]], [start[1], end[1]], 'g-', linewidth=2, label='Start→End')
    ax.scatter([start[0], end[0]], [start[1], end[1]], color='green', s=50)
    ax.text(start[0] + 0.3, start[1], 'Start', fontsize=12, color='green')
    ax.text(end[0] + 0.3, end[1], 'End', fontsize=12, color='green')
    
    # Arrow pointing to End point
    ax.annotate('Output End', xy=end, xytext=(end[0] + 2, end[1] + 2),
                arrowprops=dict(facecolor='black', shrink=0.05), fontsize=12)
    
    ax.set_xlim(-7, 7)
    ax.set_ylim(-7, 7)
    ax.set_aspect('equal')
    ax.grid(True)
    ax.set_title('Case 1: Start and End are both inside the window')
    plt.savefig(r'd:\mygit_code\program\woven0828\draw\case_1.png', dpi=300, bbox_inches='tight')
    plt.close()

def draw_case_2():
    fig, ax = plt.subplots(figsize=(8, 6))
    
    # Draw the clipping window
    rect = patches.Rectangle((-5, -5), 10, 10, linewidth=2, edgecolor='black', facecolor='none')
    ax.add_patch(rect)
    
    # Draw the line segment (Start inside, End outside)
    start = (2, 2)
    end = (6, 6)
    ax.plot([start[0], end[0]], [start[1], end[1]], 'b-', linewidth=2, label='Start→End')
    ax.scatter([start[0], end[0]], [start[1], end[1]], color='blue', s=50)
    ax.text(start[0] + 0.3, start[1], 'Start', fontsize=12, color='blue')
    ax.text(end[0] + 0.3, end[1], 'End', fontsize=12, color='blue')
    
    # Intersection point
    intersection = (5, 5)
    ax.scatter(intersection[0], intersection[1], color='red', s=50)
    ax.text(intersection[0] + 0.3, intersection[1], 'Intersection', fontsize=12, color='red')
    
    # Arrow pointing to intersection point
    ax.annotate('Output Intersection', xy=intersection, xytext=(intersection[0] + 2, intersection[1] + 2),
                arrowprops=dict(facecolor='black', shrink=0.05), fontsize=12)
    
    ax.set_xlim(-7, 7)
    ax.set_ylim(-7, 7)
    ax.set_aspect('equal')
    ax.grid(True)
    ax.set_title('Case 2: Start is inside, End is outside')
    plt.savefig(r'd:\mygit_code\program\woven0828\draw\case_2.png', dpi=300, bbox_inches='tight')
    plt.close()

def draw_case_3():
    fig, ax = plt.subplots(figsize=(8, 6))
    
    # Draw the clipping window
    rect = patches.Rectangle((-5, -5), 10, 10, linewidth=2, edgecolor='black', facecolor='none')
    ax.add_patch(rect)
    
    # Draw the line segment (Start outside, End inside)
    start = (-6, -6)
    end = (-2, -2)
    ax.plot([start[0], end[0]], [start[1], end[1]], 'orange', linewidth=2, label='Start→End')
    ax.scatter([start[0], end[0]], [start[1], end[1]], color='orange', s=50)
    ax.text(start[0] + 0.3, start[1], 'Start', fontsize=12, color='orange')
    ax.text(end[0] + 0.3, end[1], 'End', fontsize=12, color='orange')
    
    # Intersection point
    intersection = (-5, -5)
    ax.scatter(intersection[0], intersection[1], color='red', s=50)
    ax.text(intersection[0] + 0.3, intersection[1], 'Intersection', fontsize=12, color='red')
    
    # Arrows pointing to intersection and End points
    ax.annotate('Output Intersection', xy=intersection, xytext=(intersection[0] - 2, intersection[1] - 2),
                arrowprops=dict(facecolor='black', shrink=0.05), fontsize=12)
    ax.annotate('and End', xy=end, xytext=(end[0] - 2, end[1] - 2),
                arrowprops=dict(facecolor='black', shrink=0.05), fontsize=12)
    
    ax.set_xlim(-7, 7)
    ax.set_ylim(-7, 7)
    ax.set_aspect('equal')
    ax.grid(True)
    ax.set_title('Case 3: Start is outside, End is inside')
    plt.savefig(r'd:\mygit_code\program\woven0828\draw\case_3.png', dpi=300, bbox_inches='tight')
    plt.close()

def draw_case_4():
    fig, ax = plt.subplots(figsize=(8, 6))
    
    # Draw the clipping window
    rect = patches.Rectangle((-5, -5), 10, 10, linewidth=2, edgecolor='black', facecolor='none')
    ax.add_patch(rect)
    
    # Draw the line segment (Start and End both outside)
    start = (6, 6)
    end = (8, 8)
    ax.plot([start[0], end[0]], [start[1], end[1]], 'gray', linestyle='--', linewidth=2, label='Start→End')
    ax.scatter([start[0], end[0]], [start[1], end[1]], color='gray', s=50)
    ax.text(start[0] + 0.3, start[1], 'Start', fontsize=12, color='gray')
    ax.text(end[0] + 0.3, end[1], 'End', fontsize=12, color='gray')
    
    # Label "No Output"
    ax.text(7, 7, 'No Output', fontsize=16, color='red', ha='center', va='center')
    
    ax.set_xlim(-7, 7)
    ax.set_ylim(-7, 7)
    ax.set_aspect('equal')
    ax.grid(True)
    ax.set_title('Case 4: Start and End are both outside the window')
    plt.savefig(r'd:\mygit_code\program\woven0828\draw\case_4.png', dpi=300, bbox_inches='tight')
    plt.close()

# Generate all four cases
draw_case_1()
draw_case_2()
draw_case_3()
draw_case_4()

print("All four cases have been saved as PNG files.")
# Run this script to automatically draw and save four cases as images (case_1.png, case_2.png, case_3.png, case_4.png)
# Each image shows the clipping window and the line segment with key points for each case
# After running, you will see: All four cases have been saved as PNG files
import pygame
import numpy as np
import threading, time

# --- Simulation state ---
coil_angles = [0, 2*np.pi/3, 4*np.pi/3]  # Phase coil positions
hall_angles = [np.pi/3, np.pi, 5*np.pi/3]  # Hall sensors

rotor_angle = 0.0
rotor_speed = 0.0
rotor_torque = 0.0
hall_states = [0, 0, 0]
field_strength = 0.0
field_angle = 0.0
B_d, B_q = 0.0, 0.0

i_a = i_b = i_c = 0.0  # Phase currents (keyboard controlled)
rotor_inertia = 0.5
rotor_damping = 0.02
k_t = 1.5

running = True

# --- Motor simulation loop (1 kHz) ---
def motor_simulation():
    global rotor_angle, rotor_speed, rotor_torque, field_strength, field_angle, B_d, B_q, hall_states
    global i_a, i_b, i_c, rotor_inertia, rotor_damping

    dt = 0.001
    while running:
        # Compute stator field
        Bx = i_a*np.cos(coil_angles[0]) + i_b*np.cos(coil_angles[1]) + i_c*np.cos(coil_angles[2])
        By = i_a*np.sin(coil_angles[0]) + i_b*np.sin(coil_angles[1]) + i_c*np.sin(coil_angles[2])
        field_strength = np.sqrt(Bx**2 + By**2)
        if field_strength > 1e-6:
            field_angle = np.arctan2(By, Bx)

        # Rotor torque and dynamics
        angle_diff = (field_angle - rotor_angle + np.pi) % (2*np.pi) - np.pi
        rotor_torque = k_t * field_strength * np.sin(angle_diff) - 0.1 * rotor_speed
        rotor_speed += (rotor_torque / max(rotor_inertia, 1e-4)) * dt
        rotor_speed *= (1 - rotor_damping)
        rotor_angle += rotor_speed * dt
        rotor_angle %= 2*np.pi

        # d-q decomposition
        B_d = field_strength * np.cos(angle_diff)
        B_q = field_strength * np.sin(angle_diff)

        # Hall sensor states
        hall_states = []
        for angle in hall_angles:
            delta = (rotor_angle - angle + np.pi) % (2*np.pi) - np.pi
            hall_states.append(abs(delta) < np.deg2rad(30))

        time.sleep(dt)

# --- Simple mouse slider class ---
class Slider:
    def __init__(self, x, y, width, min_val, max_val, start_val, label):
        self.rect = pygame.Rect(x, y, width, 10)
        self.knob_x = x + (start_val - min_val)/(max_val - min_val)*width
        self.min_val = min_val
        self.max_val = max_val
        self.width = width
        self.dragging = False
        self.label = label
        self.value = start_val

    def handle_event(self, event):
        if event.type == pygame.MOUSEBUTTONDOWN and self.rect.collidepoint(event.pos):
            self.dragging = True
        elif event.type == pygame.MOUSEBUTTONUP:
            self.dragging = False
        elif event.type == pygame.MOUSEMOTION and self.dragging:
            self.knob_x = max(self.rect.left, min(event.pos[0], self.rect.right))
            self.value = self.min_val + (self.knob_x - self.rect.left)/self.width*(self.max_val - self.min_val)

    def draw(self, surface, font):
        pygame.draw.rect(surface, (180,180,180), self.rect)
        pygame.draw.circle(surface, (255,255,0), (int(self.knob_x), self.rect.centery), 8)
        text = font.render(f"{self.label}: {self.value:.3f}", True, (255,255,255))
        surface.blit(text, (self.rect.left, self.rect.top - 25))

# --- Start simulation thread ---
threading.Thread(target=motor_simulation, daemon=True).start()

# --- Pygame setup ---
pygame.init()
pygame.display.set_caption("Motor Simulator (Sliders + Keyboard Phases)")
WIDTH, HEIGHT = 800, 600
screen = pygame.display.set_mode((WIDTH, HEIGHT))
clock = pygame.time.Clock()
font = pygame.font.Font(None, 28)

# Sliders for rotor properties
inertia_slider = Slider(50, HEIGHT-100, 300, 0.1, 2.0, rotor_inertia, "Inertia")
damping_slider = Slider(50, HEIGHT-60, 300, 0.0, 0.2, rotor_damping, "Damping")

# --- Main GUI loop ---
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        inertia_slider.handle_event(event)
        damping_slider.handle_event(event)

    # Update from sliders
    rotor_inertia = inertia_slider.value
    rotor_damping = damping_slider.value

    # Keyboard phase control
    keys = pygame.key.get_pressed()
    i_a = 1.0 if keys[pygame.K_a] else (-1.0 if keys[pygame.K_q] else 0.0)
    i_b = 1.0 if keys[pygame.K_s] else (-1.0 if keys[pygame.K_w] else 0.0)
    i_c = 1.0 if keys[pygame.K_d] else (-1.0 if keys[pygame.K_e] else 0.0)

    # Draw background
    screen.fill((30,30,30))

    # Draw stator coils
    center = (WIDTH//2, HEIGHT//2)
    radius = 200
    for angle, color in zip(coil_angles, [(255,0,0),(0,255,0),(0,0,255)]):
        x = center[0] + radius*np.cos(angle)
        y = center[1] + radius*np.sin(angle)
        pygame.draw.circle(screen, color, (int(x),int(y)), 20)

    # Draw stator field
    field_x = center[0] + 120*np.cos(field_angle) * field_strength
    field_y = center[1] + 120*np.sin(field_angle) * field_strength
    pygame.draw.line(screen, (255,255,0), center, (int(field_x), int(field_y)), 4)

    # Draw rotor magnet (cyan)
    rotor_x = center[0] + 80*np.cos(rotor_angle)
    rotor_y = center[1] + 80*np.sin(rotor_angle)
    pygame.draw.line(screen, (100,200,255), center, (int(rotor_x), int(rotor_y)), 6)

    # Draw q-axis torque vector (red)
    torque_dir = rotor_angle + np.pi/2
    torque_x = center[0] + 80*np.cos(torque_dir) * (B_q/(field_strength+1e-6))
    torque_y = center[1] + 80*np.sin(torque_dir) * (B_q/(field_strength+1e-6))
    pygame.draw.line(screen, (255,50,50), center, (int(torque_x), int(torque_y)), 4)

    # Draw Hall sensors
    hall_radius = 150
    for angle, active in zip(hall_angles, hall_states):
        x = center[0] + hall_radius*np.cos(angle)
        y = center[1] + hall_radius*np.sin(angle)
        color = (0,255,0) if active else (60,60,60)
        pygame.draw.circle(screen, color, (int(x),int(y)), 10)

    # Draw sliders
    inertia_slider.draw(screen, font)
    damping_slider.draw(screen, font)

    # Display live data
    text1 = font.render(f"Rotor Angle: {np.degrees(rotor_angle):6.1f}°", True, (220,220,220))
    text2 = font.render(f"Speed: {rotor_speed:6.3f} rad/s   Torque: {rotor_torque:6.3f}", True, (220,220,220))
    text3 = font.render(f"B_d: {B_d:6.3f}   B_q: {B_q:6.3f}", True, (200,255,200))
    text4 = font.render(f"Hall: {['1' if s else '0' for s in hall_states]}", True, (255,255,0))
    text5 = font.render(f"iA: {i_a:+.1f}  iB: {i_b:+.1f}  iC: {i_c:+.1f}", True, (220,220,220))

    screen.blit(text1, (10, HEIGHT-200))
    screen.blit(text2, (10, HEIGHT-180))
    screen.blit(text3, (10, HEIGHT-160))
    screen.blit(text4, (10, HEIGHT-140))
    screen.blit(text5, (10, HEIGHT-40))

    pygame.display.flip()
    clock.tick(60)

pygame.quit()

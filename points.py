# vehicles.py
import math
EPSILON = 0.001

class Point:
    def __init__(self, coordinates):
        self.coords = tuple(coordinates)
        self.d = len(self.coords)
        self.closestCenter = None

    def updateClosestCenter(self, CenterPoints):
        for center in CenterPoints:
            dist = self.distanceTo(center)
            if self.closestCenter is None or dist < self.distanceTo(self.closestCenter):
                self.closestCenter = center

    def distanceTo(self, otherPoint):
        if self.d != otherPoint.d:
            raise ValueError("Points must have the same dimension to calculate distance.")
        return math.sqrt(sum((a - b) ** 2 for a, b in zip(self.coords, otherPoint.coords)))

class CenterPoint:
    def __init__(self, coordinates):
        self.coords = tuple(coordinates)
        self.d = len(self.coords)
        self.assignedPoints = []

    def updateCoordinates(self):
        maxDiff = 0
        if not self.assignedPoints:
            return
        new_coords = []
        for i in range(self.d):
            coord_sum = sum(point.coords[i] for point in self.assignedPoints)
            new_coords.append(round(coord_sum / len(self.assignedPoints), 4))
            if abs(new_coords[-1] - self.coords[i]) > maxDiff:
                maxDiff = abs(new_coords[-1] - self.coords[i])
        if len(new_coords) != self.d:
            raise ValueError("Dimension mismatch when updating coordinates.")
        self.coords = tuple(new_coords)
        self.assignedPoints = []
        return maxDiff > EPSILON
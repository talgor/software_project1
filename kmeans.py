from points import Point, CenterPoint
ITER = 400

def updateAllPoints(points, centerPoints):
    for point in points:
        point.updateClosestCenter(centerPoints)
        try:
            point.updateClosestCenter(centerPoints)
        except Exception as e:
            print(f"Error updating closest center for a point: {e}")
            continue
        point.closestCenter.assignedPoints.append(point)

def updateAllCenters(centerPoints):
    stopRun = True
    for center in centerPoints:
        if center.updateCoordinates():
            stopRun = False
    return stopRun

def kmeans(points, k, max_iterations=ITER):
    centerPoints = [CenterPoint(point.coords) for point in points[:k]]
    for iteration in range(max_iterations):
        updateAllPoints(points, centerPoints)
        if updateAllCenters(centerPoints):
            break
    return centerPoints
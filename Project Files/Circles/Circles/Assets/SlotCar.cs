using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SlotCar : MonoBehaviour {

    public Catmul currentSpline;
    public Catmul[] splines;
    // Use this for initialization
    public float speed = 0.5f;
    public float maxrotationspeed = 0.4f; // radians
    public float angle;
    public float crashLimit = 5.0f;
    public int nextwaypoint = 1;
    public float closeEnough = 1.0f;
    public int lane = 1;
    public int laneDirection = 1;

    void Start () {

        Vector3 pos = currentSpline.GetPoint(nextwaypoint, lane);     //newPoints[0];
        gameObject.transform.position = pos;
        Vector3 next = currentSpline.GetPoint(nextwaypoint + laneDirection, lane);    //newPoints[1];
        Vector3 direction = next - pos;

        Vector3 newDir = Vector3.RotateTowards(gameObject.transform.forward, direction, maxrotationspeed, 0.0f);
        transform.rotation = Quaternion.LookRotation(newDir);

        BoidSpawner bs = GetComponent<BoidSpawner>();
        bs.SpawnBoids(10);

    }
	
	// Update is called once per frame
	void Update () {

        Vector3 pos = gameObject.transform.position;
        Vector3 next = currentSpline.GetPoint(nextwaypoint, lane);
        Vector3 direction = next - pos;
        angle = Vector3.Angle(direction, gameObject.transform.forward);
        Vector3 newDir = Vector3.RotateTowards(gameObject.transform.forward, direction, maxrotationspeed, 0.0f);
        gameObject.transform.rotation = Quaternion.LookRotation(newDir);
        float d = speed * Time.deltaTime;
        float distanceToNextPoint = Vector3.Distance(gameObject.transform.position, currentSpline.GetPoint(nextwaypoint, lane));
        gameObject.transform.Translate(Vector3.forward * d);

        if (d > distanceToNextPoint)
        {
            CheckForLaneChange();

            SelectNextPoint();
        }
        
    }

    private void CheckForLaneChange()
    {
        for(int i = 0; i < currentSpline.points.Length; i++)
        {
            if(Vector3.Distance(currentSpline.newPoints[nextwaypoint], currentSpline.points[i].position) < 0.3f)
            {
                if (lane != 1)
                {
                    CheckForintersection(i);
                    RandomLane();
                }
                else
                {
                    RandomLane();
                }
                return;
            }
        }
    }

    private void CheckForintersection(int index)
    {
        foreach(Catmul s in splines)
        {
            if(s == currentSpline)
            {
                continue; //skip
            }
            for(int i = 0; i < s.points.Length; i++)
            {
                if(Vector3.Distance(currentSpline.points[index].position, s.points[i].position) < 0.2f)
                {
                    ChangeLaneDirection(s, i, index);
                    return;
                }
                
            }

        }
    }

    private void ChangeLaneDirection(Catmul s, int i, int j)
    {

        Vector3 A1;
        Vector3 X;
        Vector3 A2;
        Vector3 B1;
        Vector3 B2;

        int A1Index = ((currentSpline.amountOfPoints * j - laneDirection) + currentSpline.newPoints.Count) % currentSpline.newPoints.Count;
        int XIndex = currentSpline.amountOfPoints * j;
        int A2Index = ((currentSpline.amountOfPoints * j + laneDirection) + currentSpline.newPoints.Count) % currentSpline.newPoints.Count;  
        
        int B1Index = ((s.amountOfPoints * i - 1) + s.newPoints.Count) % s.newPoints.Count;     
        int B2Index = ((s.amountOfPoints * i + 1) + s.newPoints.Count) % s.newPoints.Count;

        A1 = currentSpline.newPoints[A1Index];
        X = currentSpline.newPoints[XIndex];
        A2 = currentSpline.newPoints[A2Index];

        B1 = s.newPoints[B1Index];
        B2 = s.newPoints[B2Index];

        Vector2 AV = A2 - X;
        Vector2 BV = B2 - X;
        float AB = Vector2.SignedAngle(AV, BV);

        //To make reading the check easier
        int left = 0;
        int right = 2;

        //Left lane checks when moving CCW
        if (lane == left && laneDirection == 1 && AB > 0)
        {
            laneDirection = 1;
        }
        else if (lane == left && laneDirection == 1 && AB <= 0)
        {
            laneDirection = -1;
        }
        //Left lane checks when moving CW
        else if (lane == left && laneDirection == -1 && AB > 0)
        {
            laneDirection = -1;
        }
        else if (lane == left && laneDirection == -1 && AB <= 0)
        {
            laneDirection = -1;
        }
        //Right lane checks when moving CCW
        else if (lane == right && laneDirection == 1 && AB > 0)
        {
            laneDirection = 1;
        }
        else if (lane == right && laneDirection == 1 && AB <= 0)
        {
            laneDirection = -1;
        }
        //Right lane checks when moving CW
        else if (lane == right && laneDirection == -1 && AB > 0)
        {
            laneDirection = 1;
        }
        else if (lane == right && laneDirection == -1 && AB <= 0)
        {
            laneDirection = -1;
        }
        nextwaypoint = (((s.amountOfPoints * (i - 1)) + s.newPoints.Count) % s.newPoints.Count);// - s.amountOfPoints;
        currentSpline = s;
    }

    private void RandomLane()
    {
        int laneNum = Random.Range(0, 3);
        switch (laneNum)
        {
            case 0: lane = 0; break;
            case 1: lane = 1; break;
            case 2: lane = 2; break;
        }
        SelectNextPoint();
        SelectNextPoint();
        SelectNextPoint();
    }

    private void SelectNextPoint()
    {
        nextwaypoint = ((nextwaypoint + laneDirection) + currentSpline.newPoints.Count ) % currentSpline.newPoints.Count;
    }

}

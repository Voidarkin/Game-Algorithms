using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class Catmul : MonoBehaviour
{

    public GameObject waypointPrefab;

    //Use the transforms of GameObjects in 3d space as your points or define array with desired points
    public Transform[] points;

    //Store points on the Catmull curve so we can visualize them
    public List<Vector3> newPoints = new List<Vector3>();
    public List<Vector3> leftPoints = new List<Vector3>();
    public List<Vector3> rightPoints = new List<Vector3>();


    //How many points you want on the curve
    public float amountOfPoints = 20.0f;
    public int numberOfControlPoints = 20;
    public float radius = 20.0f;

    //set from 0-1
    public float alpha = 0.5f;
    public float deltaAngle = 1.5f;

    /////////////////////////////
    private void Awake()
    {
        float angle = Random.Range(0, Mathf.PI * 2);
        points = new Transform[numberOfControlPoints];
        for (int i = 0; i < numberOfControlPoints; i++)
        {
            
            // generate a new waypoint here, and add it's transform to the points array
            Vector3 pos = Vector3.zero;
            pos.x = radius * Mathf.Cos(angle);
            pos.z = radius * Mathf.Sin(angle);
            GameObject wp = GameObject.Instantiate(waypointPrefab, pos, Quaternion.identity);
            points[i] = wp.transform;
            angle += deltaAngle;
        }

        newPoints.Clear();
        for (int i = 0; i < numberOfControlPoints; i++)
        {
            CatmulRom(i);
        }
        for (int i = 0; i < newPoints.Count; i++)
        {
            Vector3 pos = GetPoint(i, 1);
            Vector3 prev = GetPoint(i - 1, 1);
            Vector3 next = GetPoint(i + 1, 1);
            Vector3 dir = next - prev;
            Vector3 leftDir = Vector3.Cross(dir, Vector3.up).normalized;
            Vector3 leftPos = pos + leftDir;
            Vector3 rightPos = pos - leftDir;
            leftPoints.Add(leftPos);
            rightPoints.Add(rightPos);
        }

    }

    //lane 0 = left, lane 1 = middle, lane 2 = right
    public Vector3 GetPoint(int index, int lane)
    {
        index = (index + newPoints.Count) % newPoints.Count;

        if(lane == 0)
        {
            return leftPoints[index];
        }
        else if(lane == 1)
        {
            return newPoints[index];
        }
        else if(lane == 2)
        {
            return rightPoints[index];
        }
        return Vector3.zero;
    }

    void Update()
    {
        newPoints.Clear();
        for (int i = 0; i < points.Length; i++)
        {
            CatmulRom(i);
        }

    }
    int getIndex(int index)
    {
        return index % points.Length;
    }

    void CatmulRom(int index)
    {


        Vector3 p0 = points[getIndex(index + 0)].position; // Vector3 has an implicit conversion to Vector2
        Vector3 p1 = points[getIndex(index + 1)].position;
        Vector3 p2 = points[getIndex(index + 2)].position;
        Vector3 p3 = points[getIndex(index + 3)].position;

        float t0 = 0.0f;
        float t1 = GetT(t0, p0, p1);
        float t2 = GetT(t1, p1, p2);
        float t3 = GetT(t2, p2, p3);

        for (float t = t1; t < t2; t += ((t2 - t1) / amountOfPoints))
        {
            Vector3 A1 = (t1 - t) / (t1 - t0) * p0 + (t - t0) / (t1 - t0) * p1;
            Vector3 A2 = (t2 - t) / (t2 - t1) * p1 + (t - t1) / (t2 - t1) * p2;
            Vector3 A3 = (t3 - t) / (t3 - t2) * p2 + (t - t2) / (t3 - t2) * p3;

            Vector3 B1 = (t2 - t) / (t2 - t0) * A1 + (t - t0) / (t2 - t0) * A2;
            Vector3 B2 = (t3 - t) / (t3 - t1) * A2 + (t - t1) / (t3 - t1) * A3;

            Vector3 C = (t2 - t) / (t2 - t1) * B1 + (t - t1) / (t2 - t1) * B2;

            if (newPoints.Count == 0 || newPoints[newPoints.Count - 1] != C)
            {
                newPoints.Add(C);
            }
        }
    }

    float GetT(float t, Vector3 p0, Vector3 p1)
    {
        float a = Mathf.Pow((p1.x - p0.x), 2.0f) + Mathf.Pow((p1.y - p0.y), 2.0f) + Mathf.Pow((p1.z - p0.z), 2.0f);
        float b = Mathf.Pow(a, 0.5f);
        float c = Mathf.Pow(b, alpha);

        return (c + t);
    }

    //Visualize the points
    void OnDrawGizmos()
    {
        Color r = Color.red;
        r.a = 0.5f;
        Color g = Color.green;
        g.a = 0.7f;
        Color b = Color.blue;
        b.a = 0.7f;

        Gizmos.color = r;
        foreach (Vector3 pos in newPoints)
        {
            Gizmos.DrawSphere(pos, 0.1f);
        }

        Gizmos.color = g;
        foreach (Vector3 pos in leftPoints)
        {
            Gizmos.DrawSphere(pos, 0.1f);
        }

        Gizmos.color = b;
        foreach (Vector3 pos in rightPoints)
        {
            Gizmos.DrawSphere(pos, 0.1f);
        }
    }
}
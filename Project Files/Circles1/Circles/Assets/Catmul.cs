using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class Catmul : MonoBehaviour
{
    public GameObject controlPointPrefab;
    //Use the transforms of GameObjects in 3d space as your points or define array with desired points
    public Transform[] points;

    //Store points on the Catmull curve so we can visualize them
    public List<Vector3> newPoints = new List<Vector3>();

    //How many points you want on the curve
    public float amountOfPoints = 20.0f;

    //set from 0-1
    public float alpha = 0.5f;

    /////////////////////////////
    private void Awake()
    {
        points = new Transform[8];
        for (int i = 0; i < 8; i++)
        {
            Vector3 pos = transform.position;
            pos.x += Mathf.Cos(Mathf.Deg2Rad * 45 * i) * 20.0f;
            pos.z += Mathf.Sin(Mathf.Deg2Rad * 45 * i) * 20.0f;
            GameObject cp = GameObject.Instantiate(controlPointPrefab, pos, Quaternion.identity);
            points[i] = cp.transform;
        }
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


        Vector3 p0 = points[getIndex(index+0)].position; // Vector3 has an implicit conversion to Vector2
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
        float a = Mathf.Pow((p1.x - p0.x), 2.0f) + Mathf.Pow((p1.y - p0.y), 2.0f)+ Mathf.Pow((p1.z-p0.z),2.0f);
        float b = Mathf.Pow(a, 0.5f);
        float c = Mathf.Pow(b, alpha);

        return (c + t);
    }

    //Visualize the points
    void OnDrawGizmos()
    {
        Color r = Color.red;
        r.a = 0.5f;
        Gizmos.color = r;
        foreach (Vector3 temp in newPoints)
        {
            Vector3 pos = new Vector3(temp.x, temp.y, temp.z);
            Gizmos.DrawSphere(pos, 0.1f);
        }
    }
}
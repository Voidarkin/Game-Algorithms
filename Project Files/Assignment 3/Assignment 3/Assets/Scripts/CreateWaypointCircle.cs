using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CreateWaypointCircle : MonoBehaviour
{

    public GameObject controlPointPrefab;
    //Use the transforms of GameObjects in 3d space as your points or define array with desired points
    public Transform[] Points;

    //How many points you want on the curve
    public int PointNum = 10;
    public float Radius = 20.0f;


    private void Awake()
    {
        Points = new Transform[PointNum];
        for (int i = 0; i < PointNum; i++)
        {
            Vector3 pos = transform.position;
            pos.x += Mathf.Cos(Mathf.Deg2Rad * (360.0f/PointNum) * i) * Radius;
            pos.z += Mathf.Sin(Mathf.Deg2Rad * (360.0f / PointNum) * i) * Radius;
            GameObject cp = GameObject.Instantiate(controlPointPrefab, pos, Quaternion.identity);
            Points[i] = cp.transform;
        }
    }
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

}

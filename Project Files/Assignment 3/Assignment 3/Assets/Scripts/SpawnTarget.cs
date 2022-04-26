using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpawnTarget : MonoBehaviour
{

    public GameObject SpawnedTank;
    public GameObject SpawnedTarget;

    public GameObject[] TargetWaypoints;
    public GameObject[] TankWaypoints;

    public Vector3 SpawnLocation;

    public float TargetSpawnDelay = 0.3f;
    public float TankSpawnDelay = 0.5f;
    public float TargetElapsedTime = 0.0f;
    public float TankElapsedTime = 0.0f;
    // Start is called before the first frame update
    void Start()
    {
        TargetElapsedTime = 0.0f;
        TargetWaypoints = GameObject.FindGameObjectsWithTag("TargetWaypoint");       

        TankElapsedTime = 0.0f;
        TankWaypoints = GameObject.FindGameObjectsWithTag("TankWaypoint");

    }

    // Update is called once per frame
    void Update()
    {
        TargetElapsedTime += Time.deltaTime;
        TankElapsedTime += Time.deltaTime;

        if (TargetElapsedTime > TargetSpawnDelay)
        {
            if (Input.GetKey(KeyCode.W))
            {
                TargetElapsedTime = 0.0f;

                SpawnLocation = TargetWaypoints[0].transform.position;
                GameObject.Instantiate(SpawnedTarget, SpawnLocation, Quaternion.identity);

            }
        }
        if (TankElapsedTime > TankSpawnDelay)
        {
            if (Input.GetKey(KeyCode.S))
            {
                TankElapsedTime = 0.0f;

                SpawnLocation = TankWaypoints[0].transform.position;
                GameObject.Instantiate(SpawnedTank, SpawnLocation, Quaternion.identity);

            }
        }
    }
}

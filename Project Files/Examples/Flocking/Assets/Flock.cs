using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Flock : MonoBehaviour {
    public GameObject ObstaclePrefab;
    public GameObject boidPrefab;
    public int numberOfBoids = 20;
    public int numberOfObstacles = 10;
    public GameObject[] boids;
    public float spawnRadius = 10.0f;
    public float speed = 1.0f;
    public float turnspeed = 30.0f;
    public float FOV = 60; // degrees
    public float NeighborDistanceSquared = 64.0f; // avoid sqrt
    public float cohesionWeight = 1.0f;
    public float alignmentWeight = 0.0f;
    public float avoidanceWeight = 1.0f;
    public float noise = 0.1f;
    public float AvoidMininum = 3.0f;
    // Use this for initialization
    void Start () {
        Instantiate(ObstaclePrefab, transform.position, Random.rotation);
        for (int i = 0; i < numberOfObstacles; i++)
        {
            Vector3 pos = transform.position + Random.insideUnitSphere * spawnRadius;
            Instantiate(ObstaclePrefab, pos, Random.rotation);
        }
        boids = new GameObject[numberOfBoids];
        for (int i = 0; i < numberOfBoids; i++)
        {
            Vector3 pos = transform.position + Random.insideUnitSphere * spawnRadius;
            boids[i] = (GameObject) Instantiate(boidPrefab, pos,Random.rotation);
            boids[i].GetComponent<Boid>().flock = this;
        }
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}

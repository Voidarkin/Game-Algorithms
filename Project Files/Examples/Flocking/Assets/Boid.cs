using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Boid : MonoBehaviour {
    public Flock flock;
    float speed = 0;
    public Vector3 direction = Vector3.zero;
    public Vector3 forward = Vector3.zero;
    public int NeighborCount = 0;
    Vector3 noise = Vector3.zero;
	// Use this for initialization
	void Start () {
        speed = flock.speed;
	}
	
	// Update is called once per frame
	void Update () {
        forward = gameObject.transform.forward;
        Motivate();
	}
    private void LateUpdate()
    {
        Move();
    }

    bool isNeighBor(Boid b)
    {
        if (b == this)
        {
            return false;
        }
        // distance check
        Vector3 offset = b.gameObject.transform.position- transform.position;
        float ds = offset.sqrMagnitude;
        if (ds > flock.NeighborDistanceSquared)
        {
            return false;
        }
        // line of sight check
        float angle = Vector3.Angle(offset, transform.forward);
        if (angle > flock.FOV)
        {
            return false;
        }

        return true;
    }

    void Move()
    {
        // rotate
        float turnspeed = flock.turnspeed;
        Quaternion turnDirection = Quaternion.FromToRotation(Vector3.forward,direction);
        transform.rotation = Quaternion.RotateTowards(gameObject.transform.rotation, turnDirection, Time.deltaTime* turnspeed);
        // then move

        transform.position = transform.position + transform.forward * speed * Time.deltaTime;
    }

    void Motivate()
    {
        // not run into stuff is top priority
        RaycastHit hit;
        if (Physics.Raycast(transform.position, transform.forward * 2, out hit))
        {
            Debug.DrawRay(transform.position, transform.forward * 2, Color.red);
            direction = Vector3.Reflect(transform.forward, hit.normal);
            return;
            // we need to turn away from it
        }
        Vector3 Alignment = Vector3.zero;
        Vector3 Cohesion = Vector3.zero;
        Vector3 Avoidance = Vector3.zero;
        NeighborCount = 0;
        foreach (GameObject g in flock.boids)
        {
            Boid b = g.GetComponent<Boid>();
            if (isNeighBor(b))
            {
                NeighborCount++;
                Cohesion += g.transform.position;
                Alignment += g.transform.forward;
                if (Vector3.Distance(g.transform.position, transform.position) < flock.AvoidMininum)
                {
                    Avoidance += (transform.position - g.transform.position);
                }
            }
        }
        if (NeighborCount != 0)
        {
            Cohesion = Cohesion / NeighborCount;
        }
        // normalize the three motivations
        Cohesion = Vector3.Normalize(Cohesion);
        Cohesion = Cohesion - transform.position;
        Alignment = Vector3.Normalize(Alignment);
        Avoidance = Vector3.Normalize(Avoidance);
        if (Random.Range(0, 100) < 5)
        {
            noise = UnityEngine.Random.onUnitSphere * flock.noise * (flock.boids.Length - NeighborCount);
        }
        // and add and scale them
        direction = Cohesion * flock.cohesionWeight + Alignment * flock.alignmentWeight + Avoidance * flock.avoidanceWeight + noise;
        // then renormalize again
        direction = Vector3.Normalize(direction);
    }
    private void OnDrawGizmos()
    {
        Gizmos.color = Color.red;
        Gizmos.DrawSphere(transform.position+direction, 0.1f);
    }
}

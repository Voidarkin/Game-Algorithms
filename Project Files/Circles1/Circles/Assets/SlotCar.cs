using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SlotCar : MonoBehaviour {
    public Catmul spline;
    // Use this for initialization
    public float speed = 0.5f;
    public float maxrotationspeed = 0.4f; // radians
    public float angle;
    public float crashLimit = 5.0f;
    public int nextwaypoint = 1;
	void Start () {
        Vector3 pos = spline.newPoints[0];
        gameObject.transform.position = pos;
        Vector3 next = spline.newPoints[1];
        Vector3 direction = next - pos;

        Vector3 newDir = Vector3.RotateTowards(gameObject.transform.forward, direction, maxrotationspeed, 0.0f);
        transform.rotation = Quaternion.LookRotation(newDir);
        BoidSpawner bs = GetComponent<BoidSpawner>();
        bs.SpawnBoids(10);
    }
	
	// Update is called once per frame
	void Update () {

        // try to move towards the next point
        // if close enough, select the subsequent point to get to.
        // we also need to know if we've gone to fast for the track.  For now, lets not worry about that, and just
        // animate along it.
        Vector3 pos = gameObject.transform.position;
        Vector3 next = spline.newPoints[nextwaypoint];
        Vector3 direction = next - pos;
        angle = Vector3.Angle(direction, gameObject.transform.forward);
        Vector3 newDir = Vector3.RotateTowards(gameObject.transform.forward, direction, maxrotationspeed, 0.0f);
        gameObject.transform.rotation = Quaternion.LookRotation(newDir);
        float distanceToMove = speed * Time.deltaTime;
        gameObject.transform.Translate(Vector3.forward * distanceToMove);

        if (Vector3.Distance(gameObject.transform.position,spline.newPoints[nextwaypoint]) < distanceToMove)
        {
            nextwaypoint++;
            if (nextwaypoint == spline.newPoints.Count)
            {
                nextwaypoint = 0;
                AdjustSpeed();
                BoidSpawner bs = GetComponent<BoidSpawner>();
                bs.SpawnBoids(5);
            }
        }
    }

    void AdjustSpeed()
    {
        speed *= 1.1f;
        if (speed > 20.0f)
        {
            speed = 20.0f;
        }

    }
}

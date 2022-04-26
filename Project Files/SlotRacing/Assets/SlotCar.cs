using UnityEngine;
using System.Collections;
using System.Collections.Generic;


public class SlotCar : MonoBehaviour {
    public Catmul spline;
    // Use this for initialization
    public float speed = 0.00f;
    public float maxrotationspeed = 0.4f; // radians
    public float angle;
    public float crashLimit = 5.0f;
    public int nextwaypoint = 1;
    public float closeEnough = 0.1f;
    public bool crashed = false;
    public int lane = 1;
	void Start () {
        Vector3 pos = spline.GetPoint(0, lane);     //newPoints[0];
        gameObject.transform.position = pos;
        Vector3 next = spline.GetPoint(1, lane);    //newPoints[1];
        Vector3 direction = next - pos;

        Vector3 newDir = Vector3.RotateTowards(gameObject.transform.forward, direction, maxrotationspeed, 0.0f);
        transform.rotation = Quaternion.LookRotation(newDir);
    }
	
	// Update is called once per frame
	void Update () {
        if (crashed == false)
        {
            if (Input.GetMouseButtonDown(0))
            {
                lane--;
                if(lane < 0)
                {
                    lane = 0;
                }
                SelectNextPoint();
                SelectNextPoint();
                SelectNextPoint();
                SelectNextPoint();
            }
            if (Input.GetMouseButtonDown(1))
            {
                lane++;
                if(lane == 3)
                {
                    lane = 2;
                }
                SelectNextPoint();
                SelectNextPoint();
                SelectNextPoint();
                SelectNextPoint();
            }


            AdjustSpeed();
            // try to move towards the next point
            // if close enough, select the subsequent point to get to.
            // we also need to know if we've gone to fast for the track.  For now, lets not worry about that, and just
            // animate along it.
            Vector3 pos = gameObject.transform.position;
            Vector3 next = spline.GetPoint(nextwaypoint, lane);
            Vector3 direction = next - pos;
            angle = Vector3.Angle(direction, gameObject.transform.forward);
            Vector3 newDir = Vector3.RotateTowards(gameObject.transform.forward, direction, maxrotationspeed, 0.0f);
            gameObject.transform.rotation = Quaternion.LookRotation(newDir);
            float d = speed * Time.deltaTime;
            float distanceToNextPoint = Vector3.Distance(gameObject.transform.position, spline.GetPoint(nextwaypoint, lane));
            gameObject.transform.Translate(Vector3.forward * speed*Time.deltaTime);

            if (d > distanceToNextPoint)
            {
                SelectNextPoint();
            }

            CheckForCrash();
        }
        else
        {
            if (speed > 0.00f)
            {
                speed *= 0.95f;
                gameObject.transform.Translate(Vector3.forward * speed*Time.deltaTime);
            }
            if (Input.GetMouseButtonDown(2))
            {
                Debug.Log("Middle button clicked when crashed");
                crashed = false;
            }
        }
    }

    private void SelectNextPoint()
    {
        nextwaypoint++;
        if (nextwaypoint == spline.newPoints.Count)
        {
            nextwaypoint = 0;
        }
    }

    void AdjustSpeed()
    {
        var d = Input.GetAxis("Mouse ScrollWheel");
        if (d > 0f)
        {
            speed += 0.5f;
            //if (speed > 20f)
            //{
            //    speed = 20f;
            //}
        }
        else if (d < 0f)
        {
            speed -= 0.5f;
            if (speed <0.0f)
            {
                speed = 0.0f;
            }
        }
    }

    void CheckForCrash()
    {
        if (speed*Time.deltaTime * angle > crashLimit)
        {
            Debug.Log(speed * angle);
            Debug.Log("Crashed");
            crashed = true;
        }
        else if (speed*Time.deltaTime * angle > crashLimit*.7f)
        {
            Debug.Log(speed * angle);
            Debug.Log("Skidding");
        }
    }
}

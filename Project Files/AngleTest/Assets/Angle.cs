using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Angle : MonoBehaviour {
    public GameObject target;
    public float fov = 20.0f;
    public Material CanSee;
    public Material CannotSee;
    public float ang;
    public float viewDis = 10.0f;
    public float d;
    public float viewDistanceSquared;

    // Update is called once per frame
    void Update()
    {
        viewDistanceSquared = viewDis * viewDis;
        Vector3 targetdir = target.transform.position - transform.position;
        ang = Vector3.Angle(targetdir, transform.forward);
        //d = Vector3.Distance(target.transform.position, transform.position);
        if (ang < fov && targetdir.sqrMagnitude < viewDistanceSquared)
        {
            //TODO: replace these checks with a bool and check if it is dirty
            if (target.GetComponent<Renderer>().material != CanSee)
            { 
                target.GetComponent<Renderer>().material = CanSee;
            }
        }
        else
        {
            if (target.GetComponent<Renderer>().material != CannotSee)
            {
                target.GetComponent<Renderer>().material = CannotSee;

            }
        }
    }

    private void OnDrawGizmos()
    {
        // we want to draw a line along FOV
        Vector3 f = transform.forward * viewDis;
        Vector3 f1 = Quaternion.AngleAxis(fov, Vector3.up) * f;
        Vector3 f2 = Quaternion.AngleAxis(-fov, Vector3.up) * f;
        Vector3 f3 = Quaternion.AngleAxis(fov, Vector3.right) * f;
        Vector3 f4 = Quaternion.AngleAxis(-fov, Vector3.right) * f;
        Gizmos.color = Color.blue;
        Gizmos.DrawRay(transform.position, f);
        Gizmos.color = Color.green;
        Gizmos.DrawRay(transform.position, f1);
        Gizmos.DrawRay(transform.position, f2);
        Gizmos.color = Color.red;
        Gizmos.DrawRay(transform.position, f3);
        Gizmos.DrawRay(transform.position, f4);


    }
}

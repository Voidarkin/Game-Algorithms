using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Shooting : Task { 
    public LineRenderer line;
    public int segmentCount = 10;
    public float chaos = 0.3f;
    public bool bHasShotTarget = false;
    public int shotDamage = 10;

    public float shotDelay = 0.4f;
    public float delayTimer = 0.4f;

// Use this for initialization
public override void Reset()
    {
        line = tree.gameObject.GetComponentInParent<LineRenderer>();
        segmentCount = 10;
        chaos = 0.3f;
        shotDamage = 10;
        bHasShotTarget = false;
        delayTimer = shotDelay;
        base.Reset();
    }

    // Update is called once per frame
    public override NodeResult Execute()
    {
        delayTimer -= Time.deltaTime;

        GameObject Muzzle = tree.gameObject.transform.Find("Muzzle").transform.Find("MuzzlePoint").gameObject;
        
        RaycastHit hit;
        Vector3 start = Muzzle.transform.position;
        Vector3 end = Muzzle.transform.forward * 10;
        bool ray = Physics.Raycast(start, end, out hit);
        Debug.DrawRay(start, end, Color.red);
        if (ray)
        {
            if (hit.collider.CompareTag("Target") && delayTimer <= 0.0f)
            {
                delayTimer = shotDelay;

                line = tree.gameObject.GetComponentInParent<LineRenderer>();
                line.positionCount = segmentCount + 1;
                Vector3 dir = (hit.collider.transform.position - Muzzle.transform.position) / segmentCount;
                for (int i = 0; i < line.positionCount; i++)
                {
                    Vector3 pos = Muzzle.transform.position + dir * i + Random.onUnitSphere * chaos;
                    line.SetPosition(i, pos);

                }
                if (!bHasShotTarget)
                {
                    if (hit.collider.GetComponentInChildren<Health>())
                    {
                        hit.collider.GetComponentInChildren<Health>().health -= shotDamage;
                        bHasShotTarget = true;
                    }
                }

                Reset();
                return NodeResult.SUCCESS;
            }
            else
            {
                if (delayTimer <= 0.2f)
                {
                    line.positionCount = 0;
                }
                return NodeResult.RUNNING;
            }
        }
        else
        {
            if (delayTimer <= 0.2f)
            {
                line.positionCount = 0;
            }
            return NodeResult.RUNNING;
        }

    }
}

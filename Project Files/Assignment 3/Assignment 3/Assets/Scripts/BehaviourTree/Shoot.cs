using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Shoot : MonoBehaviour
{
    public Material[] mats;
    public GameObject Target;
    LineRenderer line;
    public int segmentCount = 10;
    public float chaos = 0.3f;

    // Start is called before the first frame update
    void Start()
    {
        line = GetComponent<LineRenderer>();
        line.positionCount = 0;
    }

    // Update is called once per frame
    void Update()
    {



        if (Target)
        {
            line.material = mats[Random.Range(0, mats.Length)];
            line.positionCount = segmentCount + 1;
            Vector3 dir = (Target.transform.position - gameObject.transform.position) / segmentCount;
            for (int i = 0; i < line.positionCount; i++)
            {
                Vector3 pos = gameObject.transform.position + dir * i + Random.onUnitSphere * chaos;
                line.SetPosition(i, pos);
            }
        }
        

    }
}

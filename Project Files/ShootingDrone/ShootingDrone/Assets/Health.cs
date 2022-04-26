using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Health : MonoBehaviour
{
    public int hp = 3;
    public Material low;
    public Material critical;
    public void TakeDamage()
    {
        hp--;
        if(hp == 0)
        {
            Destroy(gameObject);
        }
        if(hp == 2)
        {
            gameObject.GetComponent<Renderer>().material = low;
        }

        if (hp == 1)
        {
            gameObject.GetComponent<Renderer>().material = critical;
        }
    }
}

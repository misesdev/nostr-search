import { NextRequest, NextResponse } from "next/server";

export async function POST(request: NextRequest)
{
    const body = await request.json()

    const { pubkey } = body

    const response = await fetch('http://localhost:8080/get_user', {
        method: "post",
        body: JSON.stringify({
            pubkey: pubkey
        })
    })

    if(response.ok) 
    {
        let json_result = await response.json()

        return NextResponse.json(json_result);
    }

    return NextResponse.json({ message: "Erro when trying tke user" })
}

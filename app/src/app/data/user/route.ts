import { NextRequest, NextResponse } from "next/server";

export async function POST(request: NextRequest)
{
    const body = await request.json()

    const { pubkey } = body

    const response = await fetch(`${process.env.API_ENGINE_URL}/user/${pubkey}`, {
        method: "get",
        headers: {
            "Accept": "application/json",
            "Content-Type": "application/json"
        }
    })

    if(response.ok) 
    {
        let json_result = await response.json()

        return NextResponse.json(json_result);
    }

    return NextResponse.json({ message: "Erro when trying tke user" })
}

import Image from "next/image"

export default function Donate() {

    return (
        <div className='flex flex-col items-center mt-22'>
            <Image
                src='/logo.png'
                alt='Nostr Book Users'
                width={260}
                height={100}
                priority
            />
            <h2
                style={{ color: "#fff", fontSize: 26 }}
                className="my-2 font-bold"
            >Donate to the Projetct</h2>
        </div>
    )
}
